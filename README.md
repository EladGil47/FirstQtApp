
# FirstQtApp

**FirstQtApp** is a Qt-based application designed to manage and display soccer teams, players, and other related functionalities. This project is structured with CMake as the build system, and includes a custom library for handling team and player data.

## Project Structure

- **build/**: Contains generated files from the build process, including object files and CMake configurations.
- **Data/**: JSON files or other data files used by the application.
- **_deps/KohotLibrary/**: Custom library for handling teams, players, and other soccer-related data.
- **images/**: Directory containing image assets like `soccer_ball.png`.
- **include/**: Header files for the application's classes and functions.
- **src/**: Source files for the application's implementation.
- **resources.qrc**: Qt resource file defining the paths to assets such as images.
- **CMakeLists.txt**: CMake configuration file for building the project.

## Building the Project

To build the project, follow these steps:

1. **Navigate to the build directory:**
   ```bash
   cd build
   ```

2. **Run CMake to configure the project:**
   ```bash
   cmake ..
   ```

3. **Build the project:**
   ```bash
   make
   ```

4. **Run the application:**
   After building, the executable will be in the `build` directory. You can run it with:
   ```bash
   .build/FirstQtApp
   ```

## Dependencies

The project relies on the following:

- **Qt**: A cross-platform application development framework.
- **CMake**: A build system generator.

## Contributing

If you wish to contribute to this project, please fork the repository and create a pull request with your changes.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.