# Сборка Windows (MSVC)

Получаем исходники:
```bash
git clone --recurse-submodules https://github.com/cherep58/galament.git 
```

Для сборки проекта необходимо установить библиотеки boost и protobuf. В переменные окружения необходимо добавить следующие переменные:

**BOOST_INCLUDEDIR** - путь к include директории библиотеки boost (пример: *c:\SDK\Boost\include\boost-1_79\\*)

**BOOST_LIBRARYDIR** - путь к lib директории библиотеки boost (пример: *c:\SDK\Boost\lib\\*)

**PROTOBUF_INCLUDEDIR** - путь к include директории библиотеки protobuf (пример: *c:\SDK\protobuf-3.20.1\src\\*)

**PROTOBUF_LIBRARYDIR** - путь к include директории библиотеки protobuf (пример: *c:\SDK\protobuf-3.20.1\lib\\*)

Затем открываем файл *src\galament.sln* в MSVC и выполняем сборку. 
Проект настроен на то, что библиотеки boost и protobuf собраны с флагами */MTd* в Debug-режиме и */MT* в Release-режиме.

# Сборка UNIX (на примере Ubuntu)

Устанавливаем необходимые зависимости:
```bash
apt-get update && apt-get -y install mc cmake libboost-all-dev libprotobuf-dev protobuf-compiler
```

Получаем исходники и собираем проект:

```bash
git clone --recurse-submodules https://github.com/cherep58/galament.git 
cd galament
mkdir build && cd build
cmake ..
make
```

# Docker
Также для сборки проекта под Unix настроен docker-контейнер. В настройках docker в разделе FileSharing указываем директорию, в которую был склонирован проект.

Получаем исходники:
```bash
git clone --recurse-submodules https://github.com/cherep58/galament.git 
cd galament
```

Для запуска проекта в Docker поднимаем контейнер командой:
```bash
docker-compose up -d
```

Дожидаемся завершения и открываем терминал:
```bash
docker exec -ti galament_project_1 /bin/bash
```

Переходим в директорию проекта внутри контейнера и выполняем сборку проекта:
```bash
cd /app
mkdir build && cd build
cmake ..
make
```