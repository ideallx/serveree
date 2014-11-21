#ifndef PROMPT_H
#define PROMPT_H

#include "../../Reliable/DataUnit/CMessage.h"
#include <QDialog>

namespace Ui {
class Prompt;
}


const QByteArray AllPrompts[] = {
    "成功",
    "登录成功",
    "登出成功",
    "课件下载成功",

    "已经登录",

    "用户名不存在",
    "密码错误",
    "未知错误",
    "播放失败",

    "暂不支持该格式的文件",
    "敬请期待",
    "服务器没有响应",
    "文件已存在"
};

class Prompt : public QDialog
{
    Q_OBJECT

public:
    explicit Prompt(WORD index, QWidget *parent = 0);
    explicit Prompt(QString prompt, QWidget *parent = 0);

    ~Prompt();

private:
    Ui::Prompt *ui;
};

#endif // PROMPT_H
