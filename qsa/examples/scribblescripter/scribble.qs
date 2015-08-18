function paintText()
{
    var maxX = Canvas.width();
    var maxY = Canvas.height();

    var textInput = new LineEdit;
    textInput.text = "Hello World!!";
    textInput.label = "Text: ";

    var sx = new SpinBox;
    sx.maximum = maxX;
    sx.minimum = 0;
    sx.value = 30;
    sx.label = "x: ";

    var sy = new SpinBox;
    sy.maximum = maxY;
    sy.minimum = 0;
    sy.value = 30;
    sy.label = "y: ";

    var dx = new SpinBox;
    dx.maximum = 100;
    dx.minimum = -100;
    dx.value = 8;
    dx.label = "x: ";

    var dy = new SpinBox;
    dy.maximum = 100;
    dy.minimum = -100;
    dy.value = 8;
    dy.label = "y: ";

    var it = new SpinBox;
    it.maximum = 100;
    it.minimum = 0;
    it.value = 10;
    it.label = "Number of iterations: ";

    var startGroup = new GroupBox;
    startGroup.title = "Start";
    startGroup.add( sx );
    startGroup.add( sy );

    var deltaGroup = new GroupBox;
    deltaGroup.title = "Delta";
    deltaGroup.add( dx );
    deltaGroup.add( dy );

    var dialog = new Dialog;
    dialog.add( textInput );
    dialog.add( startGroup );
    dialog.add( deltaGroup );
    dialog.add( it );

    var ok = dialog.exec();

    if( !ok )
        return;

    var text = textInput.text;
    var x = sx.value;
    var y = sy.value;
    var dx = dx.value;
    var dy = dy.value;
    var rep = it.value;

    var can = Canvas.pixmap();
    for ( var i = 0; i < rep; i++ ) {
 can.drawText( text, x, y );
 x += dx;
 y += dy;
    }
    Canvas.setPixmap( can );
}

function lines() {
    var can = Canvas.pixmap();

//     can.clear();

    can.scale(Canvas.width() / 2, Canvas.height() / 2);
    can.translate(1, 1);

    for (var i=0; i<360; i+=10) {
        can.rotate(10);
        can.drawLine(0, 0, 0, 1);
    }

    Canvas.setPixmap(can);
}

function Qt() {
    var can = Canvas.pixmap();
    // Clear, and set geometry from (0,0) to (100,100), no matter
    // how big the actual canvas is. Eases scaled drawing :)

    can.clear();
    can.scale(Canvas.width() / 100, Canvas.height() / 100);

    // Paint background
    can.color = new Color( 167, 196, 0 );
    can.fillRect( 0, 0, 100, 100 );

    // Paint 'O' in Qt logo
    can.color = new Color( "black" );
    can.drawPie( 14, 14, 72, 72, 0, 5760 ); // 5760 = (16 * 360)

    can.color = new Color( 167, 196, 0 );
    can.drawPie( 26, 26, 48, 48, 0, 5760 );

    // Rotate the coordinate system
    can.rotate( -45.0 );

    // Paint the 't' in Qt logo
    can.color = new Color( "black" );
    can.fillRect( 5, 75, -11, 39 );
    can.fillRect( -17, 64, 34, 13 );

    Canvas.setPixmap( can );
}

function simpleGradient()
{
    var can = Canvas.pixmap();
    var height = Canvas.height();

    for (var y=0; y < height; ++y) {
	can.color = new Color(255 * (height - y) / height, 0, 255 * y / height);
	can.fillRect(0, y, Canvas.width(), 1);
    }

    Canvas.setPixmap(can);
}
