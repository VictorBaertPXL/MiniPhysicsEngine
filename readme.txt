Mini Physics Engine

Beschrijving:
Een kleine 2D fysica-simulatie in C++ met objectgeoriënteerde technieken zoals inheritance, polymorfisme, encapsulation en composition. Ondersteunt Ball en Block objecten in een World, met threads voor realtime updates en logging naar bestand.

Features:
- PhysicsObject base class
- Ball en Block subclasses
- Threaded simulation loop
- Template Logger voor posities
- Exception handling en dynamic memory management

Build:
1. Compileer met g++:
   g++ -std=c++17 src/*.cpp -Iinclude -pthread -o MiniPhysicsEngine
2. Run de executable:
   ./MiniPhysicsEngine
