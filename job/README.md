# Trajectory viewer


*This project creates a .deb package that can later be run on Linux systems, which was tested on Ubuntu and Astra Linux.*


### How to run deb packaging:

1. Clone the project: ```git clone https://github.com/Alex410023/main.git```
2. Move to the project directory: ```cd job/trajectory_viewer/trajectory_viewer```
3. Build the deb package: ```mvn clean package -Pdeb```
4. Install the package: ```sudo dpkg -i target/trajectory_viewer-1.0-SNAPSHOT.deb```
5. Run the application: ```trajectory-viewer```
