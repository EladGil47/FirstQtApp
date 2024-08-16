FirstQtApp

FirstQtApp is a Qt-based application developed with CMake. This project demonstrates a basic application structure using the Qt framework, with features like custom UI components and resource management.
Project Structure

The project is organized as follows:

makefile

.
├── build/                     # Build artifacts and CMake files
├── Data/                      # Data files (e.g., JSON)
├── _deps/                     # Project dependencies
│   ├── KohotLibrary/          # Kohot library sources and headers
├── images/                    # Image resources
├── include/                   # Header files for the application
├── src/                       # Source code for the application
├── resources.qrc              # Qt resource file
├── CMakeLists.txt             # CMake configuration file
└── README.md                  # Project documentation

Key Directories

    build/: Contains all generated files after compiling the project. This includes object files, CMake configurations, and other intermediate build files.

    Data/: Stores external data files required by the application, such as groups.json.

    _deps/: Holds external dependencies, such as the KohotLibrary, with their respective source and header files.

    images/: Contains image assets used in the application, such as soccer_ball.png.

    include/: Header files that define the interface for the application's components and features.

    src/: Source files that implement the application's functionality.

Getting Started
Prerequisites

    Qt 5.x+: Make sure you have Qt installed.
    CMake 3.21+: CMake is required to build the project.
    C++ Compiler: A modern C++ compiler that supports C++17 or later.

Building the Project

    Clone the repository:

    bash

git clone https://github.com/yourusername/FirstQtApp.git
cd FirstQtApp

Create a build directory and run CMake:

bash

mkdir build
cd build
cmake ..

Compile the project:

bash

cmake --build .

Run the application:

bash

    ./KohotQtApp

Project Features

    Custom UI Components: Includes various UI widgets like CheckablePlayerItemWidget, EditableLabel, and more.
    Resource Management: Centralized resource management using resources.qrc.
    Data Integration: Handles JSON data files to manage groups and players.

Adding Resources

To add new resources (e.g., images), follow these steps:

    Place the new resource in the images/ directory.
    Update the resources.qrc file to include the new resource:

    xml

    <file>./images/your_new_image.png</file>

    Rebuild the project to include the new resource.

Contributing

Contributions are welcome! If you have suggestions or find any issues, please feel free to open an issue or submit a pull request.
License

This project is licensed under the MIT License - see the LICENSE file for details.

This README provides a clear overview of your project, how to get started, and the structure. You can modify the sections to fit additional features or instructions specific to your project.