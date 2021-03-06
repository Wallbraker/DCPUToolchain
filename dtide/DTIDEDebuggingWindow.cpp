#include "DTIDEDebuggingWindow.h"

DTIDEDebuggingWindow::DTIDEDebuggingWindow(QWidget* parent): QDialog(parent)
{
    buffer = 0;

    setupUi(this);
    connect(btn_step_into, SIGNAL(clicked()), this, SIGNAL(step()));
    connect(btn_resume, SIGNAL(clicked()), this, SIGNAL(resume()));
    connect(btn_pause, SIGNAL(clicked()), this, SIGNAL(pause()));

    initializeBuffer();

    memoryView->setWordWidth(2);
    memoryView->setShowAsciiDump(false);
    memoryView->setRowWidth(8);
    memoryView->setShowAddressSeparator(false);
}

QSize DTIDEDebuggingWindow::sizeHint()
{
    return QSize(400, 400);
}

void DTIDEDebuggingWindow::setRegisters(StatusMessage m)
{
    QStringList registers;
    for (int i = 0; i < 8; i++)
    {
        QString r = QString("0x%1").arg(m.registers[i], 4, 16, QChar('0'));
        registers.append(r);
    }

    // TODO: Fix this mess.

    reg_A->setText(registers[0]);
    reg_B->setText(registers[1]);
    reg_C->setText(registers[2]);
    reg_X->setText(registers[3]);
    reg_Y->setText(registers[4]);
    reg_Z->setText(registers[5]);
    reg_I->setText(registers[6]);
    reg_J->setText(registers[7]);

    reg_PC->setText(QString("0x%1").arg(m.pc, 4, 16, QChar('0')));
    reg_SP->setText(QString("0x%1").arg(m.sp, 4, 16, QChar('0')));
    reg_EX->setText(QString("0x%1").arg(m.ex, 4, 16, QChar('0')));
    reg_IA->setText(QString("0x%1").arg(m.ia, 4, 16, QChar('0')));
}

void DTIDEDebuggingWindow::closeEvent(QCloseEvent* e)
{
    e->accept();
    emit stop();
}

void DTIDEDebuggingWindow::setMemoryData(QByteArray* bytes)
{
    initializeBuffer();
    QSharedPointer<QBuffer> buff_ptr(buffer);

    data = bytes;

    buffer->close();
    buffer->setBuffer(data);
    buffer->open(QIODevice::ReadWrite);

    memoryView->setData(buff_ptr);
}

void DTIDEDebuggingWindow::setMemoryAt(int pos, char v1, char v2)
{
    char replacement[3] = { v1, v2, 0 };
    data->replace(pos * 2, 2, replacement, 2);

    setMemoryData(data);
}

void DTIDEDebuggingWindow::initializeBuffer()
{
//    if(buffer != 0)
//        delete buffer;

    data = new QByteArray();
    buffer = new QBuffer(data);
    buffer->open(QIODevice::ReadWrite);
}
