# Messenger

## О проекте

**Messenger** — pet-проект для изучения клиент-серверного взаимодействия, WebSocket, CI/CD, Docker и PostgreSQL. Проект состоит из двух частей: серверной и клиентской, реализующих взаимодействие в реальном времени через WebSocket.  
Основная цель — изучить практику построения сетевого приложения, освоить работу с TCP/IP, WebSocket, CI/CD, Docker, взаимодействие с PostgreSQL и разработку GUI на Qt.

---

## Технологический стек

| Компонент      | Назначение                                   |
|----------------|----------------------------------------------|
| **C++**        | Язык реализации логики клиента и сервера     |
| **Qt5**        | Фреймворк для GUI, сетей, работы с БД        |
| **WebSocket**  | Протокол обмена сообщениями в реальном времени |
| **PostgreSQL** | Хранение пользователей, сообщений, токенов           |
| **CMake**      | Кроссплатформенная система сборки            |
| **Docker**     | (Планируется) Контейнеризация                |
| **CI/CD**      | (Планируется) Автоматизация сборки и тестов  |

---

## TODO

- [X] Инициализация базы данных
- [X] Хэширование паролей
- [ ] Защищенное соединение
- [ ] Реализация отображения пользователей онлайн
- [ ] Реализация обмена сообщениями
- [ ] Реализация истории сообщений
- [ ] Реализация обмена файлами
- [ ] Групповые чаты
- [ ] Сборка под Linux
- [ ] Ui/Ux
- [ ] Push уведомления
- [ ] Локализация и поддержка языков
- [ ] CI/CD
- [ ] Контейнеризация
- [ ] Документация
- [ ] Мобильный клиент

---

## Функциональность

- **Сервер:**
  - Запуск WebSocket-сервера на Qt5 для обработки клиентских соединений.
  - Инициализация базы данных PostgreSQL
  - Приём и обработка JSON-команд от клиента: регистрация, вход, обмен сообщениями и файлами.
  - Хэширование данных пользователей.
  - Генерация и обновление токенов.
  - Генерация SSL сертификата.
  - Логирование операций и ошибок.
- **Клиент:**
  - Графический интерфейс на QtWidgets (окно авторизации, окно чата).
  - WebSocket-клиент для обмена данными с сервером.
  - Отправка команд регистрации и входа, получение результатов.
  - Обмен сообщений и файлами.

---

## Подробности реализации

### Сервер

- **MessengerServer** запускает WebSocket-сервер и слушает входящие соединения.
- Для каждого нового клиента создаётся обработчик, который:
  - Принимает JSON-команды (`register`, `login`, в будущем — отправка сообщений).
  - Выполняет SQL-запросы к PostgreSQL: регистрация, вход, проверка пароля.
  - Формирует JSON-ответы для клиента.
- Используется таймер для периодической отправки ping-пакетов, отслеживания соединений.
- Пароли хранятся в базе в открытом виде — требуется внедрение хэширования.

### Клиент

- **AuthWindow** — окно авторизации, реализованное на QtWidgets.
- **WebSocketClient** — компонент для подключения к серверу по WebSocket, отправки команд и приёма ответов.
- Вся коммуникация между клиентом и сервером идёт по JSON через WebSocket.
- На данный момент реализованы функции регистрации и входа.  
  В планах — полноценный чат и отображение истории сообщений.

---

## Как запустить

### Windows

#### Сервер

#### Клиент

### Linux

#### Сервер

#### Клиент

---

## Лицензия

Проект распространяется на условиях лицензии [MIT](LICENSE).

```
MIT License

Copyright (c) 2025 Ky0k01

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---
