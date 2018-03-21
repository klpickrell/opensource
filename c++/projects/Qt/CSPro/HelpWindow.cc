#include <QTextEdit>
#include <sstream>

#include "HelpWindow.h"

HelpWindow::HelpWindow( QWidget* parent ) : 
    QDialog( parent )
{
    setAttribute( Qt::WA_DeleteOnClose );
    setWindowTitle( "CacheSimulation Pro Help" );
    resize( 150, 200 );

    QTextEdit* text = new QTextEdit( this );

    std::ostringstream html_text;
    html_text << "<html><head><title>Help Menu</title></head>"
              << "<body>"
              << "<i>CacheSimulation Pro v0.1</i>"
              << "<hr>"
              << "<a href=./stub.txt>Enter Search Query</a><br>"
              << "<a href=./stub.txt>Frequently Asked Questions</a><br>"
              << "<a href=./stub.txt>Table of Contents</a><br>"
              << "<hr>"
              << "Copyright (c) 2009"
              << "</body>";

    text->setHtml( QString::fromStdString( html_text.str() ) );
}
