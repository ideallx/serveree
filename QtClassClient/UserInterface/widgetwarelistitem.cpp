#include "widgetwarelistitem.h"
#include "ui_widgetwarelistitem.h"

WidgetWareListItem::WidgetWareListItem(QByteArray filename, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetWareListItem),
    m_filename(filename) {
    ui->setupUi(this);
}

WidgetWareListItem::~WidgetWareListItem() {
    delete ui;
}

void WidgetWareListItem::on_tbRun_clicked() {
    emit runFile(m_filename);
}

void WidgetWareListItem::on_tbRemove_clicked() {
    emit removeFile(m_filename);
}
