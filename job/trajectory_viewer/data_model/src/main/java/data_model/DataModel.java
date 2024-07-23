package data_model;

import java.io.IOException;

import java.util.List;
import java.util.Scanner;

public class DataModel {
    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            // Standard path
            String filePath = "data_model/src/main/resources/traject1.txt";

            List<MovingPoint> trajectory = TrajectoryReader.readTrajectoryFromFile(filePath);
            FileDetails fileDetails = TrajectoryReader.extractFileDetails(filePath);

            // Display file details
            System.out.println("\nFile Details:");
            System.out.println("Path: " + fileDetails.getPath());
            System.out.println("Format: " + fileDetails.getFormat());
            System.out.println("Content: " + fileDetails.getContent());

            // Display trajectory data
            System.out.println("\nTrajectory Data:");
            for (MovingPoint position : trajectory) {
                System.out.println("Time: " + position.getTime() +
                        " X: " + position.getPoint().getX() +
                        " Y: " + position.getPoint().getY() +
                        " Z: " + position.getPoint().getZ() +
                        " VelocityX: " + position.getVelocityX() +
                        " VelocityY: " + position.getVelocityY() +
                        " VelocityZ: " + position.getVelocityZ());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
