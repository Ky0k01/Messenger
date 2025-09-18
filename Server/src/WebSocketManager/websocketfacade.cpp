#include "websocketfacade.h"

WebSocketFacade::WebSocketFacade(Logger *logger, QObject *parent): logger(logger), QObject(parent){
    webSocketStartupManager = new WebSocketStartupManager(server);
    sessionManager = new SessionManager(this);
    socketManager = new WebSocketManager(this->logger, this);
    invokeCommandManager = new InvokeCommandManager(this);
    receiveCommandManager = new ReceiveCommandManager(server, this);
}

WebSocketFacade::~WebSocketFacade(){
    delete webSocketStartupManager;
    delete sessionManager;
    delete invokeCommandManager;
    delete receiveCommandManager;
}


void WebSocketFacade::runStateMachine(){
    processStateMachine(START_STATE);
}

void WebSocketFacade::processStateMachine(int currentState){
    switch (currentState){
        case START_STATE:{
            if(logger->checkWorkingState() != true) logger->startLogger();

            logger->printTerminal("WebSocketManager", "Messenger WebSocket Server v0.1"); // сделать вывод версии из переменной
            logger->printTerminal("WebSocketManager", "Starting...");

            setConnections();

            server = webSocketStartupManager->startServer();

            processStateMachine(CONFIGURATION_STATE);
            break;
        };

        case CHECK_UPDATE_STATE:{ // на будущее
            break;
        };

        case UPDATING_STATE:{     // на будущее
            break;
        };

        case CONFIGURATION_STATE:{
            try{
                startServer();
                processStateMachine(READY_STATE);
            }
            catch(const WebSocketException& ex){
                cout << ex.what() << endl;
                logger->writeLogLine("WebSocket", ex.what(), "Error");
                processStateMachine(CONFIGURATION_STATE);
            }
            catch(...){
                processStateMachine(CONFIGURATION_STATE);
            }
            break;
        };

        case READY_STATE:{
            QTextStream in(stdin);
            while(true){
                while(!in.atEnd()){
                    QString line = in.readLine().trimmed();
                    if (line.isEmpty()) continue;
//                    command(line);
                }
            }
            break;
        };

        default:{

        };
    }
}


void WebSocketFacade::setConnections(){
    connect(socketManager, &WebSocketManager::writeAnonymousSocket, sessionManager, &SessionManager::registerAnonymousSocket);
}



void WebSocketFacade::startServer(){
    setPort();
    emit initializeDatabase();
}

void WebSocketFacade::setPort(){
    int port = logger->printTerminalAndReturnInput("WebSocketManager", "Print server connection port: ").toInt();

    if(server->listen(QHostAddress::Any, port)){
        connect(server, &QWebSocketServer::newConnection, socketManager, &WebSocketManager::onNewConnection);
    }
    else{
        throw WebSocketException("Failed to listen port");
    }
}
