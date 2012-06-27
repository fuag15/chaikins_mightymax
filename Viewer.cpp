#include "Viewer.h"
#include "Window.h"


/*
Using Chaikin’s curves, draw a recognizable outline of your favorite cartoon character.
Chaikin’s curves are described in the notes.
*/

Viewer::Viewer() : QGLWidget()
{
    orig = new LNHHolder();
    current = 0;
    temp = 0;
    cursor = 0;
    noIter = false;
    
    readFile();
    
    temp = 0;
    
    iter = 3;
    
    resize(400, 400);
}

void Viewer::initializeGL()
{
    return;
}

void Viewer::runChaikin(int numIter) // runs chaikins
{
    // xA yA xB yB are the original x and y coords
    // xTa etc are teh final coords
    // xTt etc are the length to inc/dec
    // startX is the orig oint, first is the first iter, last is the last iter to handle loops
    float xA, yA, xB, yB, xTa, yTa, xTb, yTb, xTt, yTt, startX, startY, firstX, firstY, lastX, lastY;
    int i;
    bool dontD;
    bool first;
    bool again = true; // variable for the loop
    
    delete current; // removes old current
    current = new LNHHolder(); // creates new system
    
    orig -> reset(); // orig is at start
    
    do // do this loop while ther is more in orig
    {
	cursor = orig -> getCurrent(); // cursor is current
	dontD = true; // dontD set to true because we dont want to delete this pointer, well mess up orig!
	if(!(orig -> isNotLast())) // set again to false if were at the end
	{
	    again = false;
	}

	for(i = 0; i < numIter; i++) // run through cursor
	{
	    first = true; //first time keep point in firstX
	    
	    
	    lastY = 0;
	    lastX = 0;
	    firstX = 0;
	    firstY = 0;
	    
	    cursor -> reset(); // cursor reset
	    temp = new LinkNodeHolder(); // new temp to add to orig
	    startX = cursor -> getX(); // set startX
	    startY = cursor -> getY(); // set startY
	    
	    while(cursor -> hasNext()) // run through cursor
	    {
		
		xA = cursor -> getX(); // get first 2 points
		yA = cursor -> getY();
		
		cursor -> advance();
		xB = cursor -> getX();
		yB = cursor -> getY();
		
		// this finds the length
		if((xA > 0 && xB > 0) || (xA < 0 && xB < 0) || (xA == 0 && xB == 0)) //the points are both positive, or both negative or 0
		{
		    xTt =  xB - xA;
		}
		else if((xA > 0) && (xB < 0)) // xA is positive xB is negative
		{
		    xTt = fabs(xA) + fabs(xB);
		}
		else if((xA < 0) && (xB > 0)) // xA is negative xB is positive
		{
		    xTt = fabs(xA) + fabs(xB);
		}
		else if(xA == 0) // only xA is 0
		{
		    xTt = fabs(xB);
		}
		else // only xB is 0
		{
		    xTt = fabs(xA);
		}
		
		if((yA > 0 && yB > 0) || (yA < 0 && yB < 0) || (yA == 0 && yB == 0)) //the points are both positive, or both negative or 0
		{
		    yTt =  yB - yA;
		}
		else if((yA > 0) && (yB < 0)) // yA is positive yB is negative
		{
		    yTt = fabs(yA) + fabs(yB);
		}
		else if((yA < 0) && (yB > 0)) // yA is negative yB is positive
		{
		    yTt = fabs(yA) + fabs(yB);
		}
		else if(yA == 0) // only yA is 0
		{
		    yTt = fabs(yB);
		}
		else // only yB is 0
		{
		    yTt = fabs(yA);
		}
		
		xTt = fabs(xTt) * (1.0/4.0); //set x inc lenght
		yTt = fabs(yTt) * (1.0/4.0); //set y inc lengt
		
		//ADD OR SUBTRACT THE DISTANCE
		if(xA < xB)
		{
		    xTa = xA + xTt;
		    xTb = xB - xTt;
		}
		else if(xA > xB)
		{
		    xTa = xA - xTt;
		    xTb = xB + xTt;
		}
		else
		{
		    xTa = xA;
		    xTb = xB;
		}
		
		if(yA < yB)
		{
		    yTa = yA + yTt;
		    yTb = yB - yTt;
		}
		else if(yA > yB)
		{
		    yTa = yA - yTt;
		    yTb = yB + yTt;
		}
		else
		{
		    yTa = yA;
		    yTb = yB;
		}
		
		temp -> add(xTa, yTa); // add the points to temp
		temp -> add(xTb, yTb);
		
		if(first == true)
		{
		    first = false; // if its first we store the values of hte iter for loops
		    firstX = xTa;
		    firstY = yTa;
		}
		
		if((cursor -> hasNext()) == false)
		{
		    lastX = xTb; // if its last then we store the value for loops
		    lastY = yTb;
		}
	    }
	    
	    xA = cursor -> getX(); // get the last points in the string
	    yA = cursor -> getY();
	    
	    if((xA == startX) && (yA == startY)) // if its a loop add the first iter again
	    {
		temp -> add(firstX, firstY);
	    }
	    
	    if(dontD != true) // if its not the first run delete cursor
	    {
		delete cursor;
	    }
	    
	    if(dontD == true) // if its been a run end it
	    {
		dontD = false;
	    }
	    
	    cursor = temp; // set cursor to temp for next iter
	}
	
	current -> add(cursor); // add cursor to current
	
	orig -> advance(); // advance what were working with
    }
    while(again);
    return;
}

void Viewer::resizeGL(int w, int h) // sets gl up
{
    glLoadIdentity();
    glViewport(0, 0, w, h);
    glOrtho(-15, 15, -15, 15, 0, 1);
    
    return;
}

void Viewer::paintGL() // paints gl
{

    glClear(GL_COLOR_BUFFER_BIT);
    if(noIter == false) // if iter is 0 don't run chaikin
    {
	runChaikin(iter);
    }
    plotPicture();
    
    return;
}

QSize Viewer::minimumSizeHint() const
{
     return QSize(50, 50);
}

QSize Viewer::sizeHint() const
{
     return QSize(400, 400);
}

void Viewer::setIter(int x) // gets iter, if its 0 changes noIter to true to keep chaikin from running
{
    if(x == 0)
    {
	noIter = true;
    }
    else
    {
	noIter = false;
    }
    iter = x;
    updateGL();
    
    return;
}

void Viewer::plotPicture()// plots the picture
{
    float x;
    float y;
    bool again = true;
    
    if(noIter == false) // don't plot it if there were no iters, instead plot orig.
    {
	
	current -> reset(); // reset current
	
	do
	{
	    glBegin(GL_LINE_STRIP);
	    if(!(current -> isNotLast())) // if current is last, again is false
	    {
		again = false;
	    }
	    
	    cursor = current -> getCurrent(); // cursor is currents LinkNodeHolder
	    cursor -> reset(); // reset
	    
	    while(cursor -> hasNext()) // plot points in the holder
	    {
		x = cursor -> getX();
		y = cursor -> getY();
		glVertex2f(x, y);
		cursor -> advance();
	    }
	    
	    x = cursor -> getX(); // plot last points
	    y = cursor -> getY();
	    
	    glVertex2f(x, y);
	    
	    current -> advance(); // advance current
	    glEnd(); // draw segment or loop
	}
	while(again);
    }
    else // plot orig
    {
	orig -> reset();
	
	do
	{
	    glBegin(GL_LINE_STRIP);
	    if(!(orig -> isNotLast()))
	    {
		again = false;
	    }
	    
	    cursor = orig -> getCurrent();
	    cursor -> reset();
	    
	    while(cursor -> hasNext())
	    {
		x = cursor -> getX();
		y = cursor -> getY();
		glVertex2f(x, y);
		cursor -> advance();
	    }
	    
	    x = cursor -> getX();
	    y = cursor -> getY();
	    
	    glVertex2f(x, y);
	    
	    orig -> advance();
	    glEnd();
	}
	while(again);
	
    }
    
    
    return;
}

void Viewer::readFile() // reads a file
{
    float x, y; // 2 points
    int i; // counting variable
    QString line, filename; //current line and file name
    QDir dir; // QDir to access current directory
    QFileInfo fileInfo; // stores info on each file
    QStringList coordList; // list of floats
    bool firstRun; // if its first run dont add temp
    QFile* theSource;// file pointer so i can handle X number of files
    
    theSource = 0; // set file pointer to null
    
    orig -> reset();
    
    dir.setFilter(QDir::Files);// sets a filter so it only gives me file names
    QFileInfoList list = dir.entryInfoList(); // contains list of all files in document
    for (i = 0; i < list.size(); ++i) // iterate through al files
    {
	fileInfo = list.at(i); // get the fileInfo
	filename = fileInfo.fileName(); // get the name
	if(filename.endsWith(".boone")) // this is a .boone FILE!
	{
	    firstRun = true; // dont add a blank member
	    //QFile theSource(filename); // file name
	    theSource = new QFile(filename);

	    theSource -> open(QIODevice::ReadOnly | QIODevice::Text);// opens file

	    QTextStream stream( theSource ); // Set the stream to read
	    while( !stream.atEnd())// while theres more file
	    {
		line = stream.readLine();// read a line
		if(line.contains("newObject")) // if it does it is a new object
		{
		    if(firstRun) // dont add a blank linknodeholder
		    {
			firstRun = false;
			temp = new LinkNodeHolder();
		    }
		    else // add old completed one and make a new one
		    {
			orig -> add(temp);
			temp = new LinkNodeHolder();
		    }
		}
		else
		{
		    coordList = line.split(" "); // splits line into list of 2 floats
		    x = coordList.at(0).toFloat(); // convert both strings to floats
		    y = coordList.at(1).toFloat();
		    temp -> add(x, y); // add the floats to the system
		}
	    }
	    
	    delete theSource; //frees up space that won't be used again;
	    
	    orig -> add(temp); // add the last one assumes a non black file
	}
    }
    
    orig -> reset(); // reset the orig queue

    return;
}

void Viewer::mousePressEvent(QMouseEvent* event)// reload file when clicked
{
    event = 0; // gets rid of warning that QMouseEvent* is not used
    delete orig; // remove anything that was in orig
    orig = new LNHHolder();
    readFile();
    updateGL();
}
