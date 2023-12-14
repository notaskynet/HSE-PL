# envoirenment variables
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")

add_executable(optimalprimer
    main.cpp
    Chat.hpp
    UDPSocket.hpp
)
