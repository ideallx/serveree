#ifndef PROMPT_H
#define PROMPT_H

#include "../../Reliable/DataUnit/CMessage.h"
#include <QDialog>

namespace Ui {
class Prompt;
}


enum PromptController {
    PromptControllerConfirm         = 1,
    PromptControllerCancel          = 2,
    PromptControllerProgressBar     = 4,
};


const QByteArray AllPrompts[] = {
    "成功",
    "登录成功",
    "登出成功",
    "课件下载成功",

    "已经登录",
    "您的账号已在别处登录，请稍后重试",

    "用户名不存在",
    "密码错误",
    "未知错误",
    "该课堂不存在",
    "播放失败",

    "暂不支持该格式的文件",
    "敬请期待",
    "服务器没有响应",
    "文件已存在",

    "课程装载中"
};

class Prompt : public QDialog
{
    Q_OBJECT

public:
    explicit Prompt(WORD index, WORD controller, QWidget *parent = 0);
    explicit Prompt(QString prompt, WORD controller, QWidget *parent = 0);

    void setPrompt(int result);
    void setPrompt(QString prompt);

    static QString getPrompt(int index);

    void setProgress(int);


    ~Prompt();

signals:
    void progressChanged(int value);

private slots:
    void on_pbConfirm_clicked();

    void on_pbCancel_clicked();


private:
    void changeLayout(WORD controller);

private:
    static bool isExist;
    Ui::Prompt *ui;
};

#endif // PROMPT_H
