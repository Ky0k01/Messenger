#include "jsonfactory.h"

QJsonObject JsonFactory::create(const QString& type, const QVariantMap& params){
    QJsonObject obj;

    if(type == "Registration"){
        obj["package"]="Registration";
        obj["login"]=params.value("login").toString();
        obj["password"]=params.value("password").toString();
    }
    else if(type == "Login"){
        obj["package"] = "Login";
        obj["login"] = params.value("login").toString();
        obj["password"] = params.value("password").toString();
        obj["sessionToken"] = params.value("token").toString();
    }
    else if(type == "AutoLogin"){
        obj["package"] = "AutoLogin";
        obj["autoLoginToken"] = params.value("token").toString();
    }
    else if(type == "Message"){
        obj["package"] = "Message";
        obj["sender_username"] = params.value("sender_username").toString();
        obj["receiver_username"] = params.value("receiver_username").toString();
        obj["message"] = params.value("message").toString();
        obj["timestamp"] = params.value("timestamp").toString();
        obj["sessionToken"] = params.value("sessionToken").toString();
    }
    else if(type == "abcd"){ // шаблон для будущих пакетов
        obj["package"] = "";
        obj[""] = params.value("").toString();
    }

    return obj;
}
