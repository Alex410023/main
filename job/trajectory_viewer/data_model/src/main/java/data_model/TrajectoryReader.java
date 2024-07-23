package data_model;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;
import java.util.List;


public class TrajectoryReader {
    public static List<MovingPoint> readTrajectoryFromFile(String filePath) throws IOException {
        List<MovingPoint> trajectories = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] strSplit = line.split("\\s+");
                List<String> values = new ArrayList<>(Arrays.asList(strSplit));

                if (values.size() != 7) {
                    System.out.println("Invalid line: " + line);
                    continue;
                }

                try {
                    MovingPoint movingPoint = new MovingPoint();

                    movingPoint.setTime(Double.parseDouble(values.get(0)));
                    movingPoint.setPoint(new Point(
                            Double.parseDouble(values.get(1)),
                            Double.parseDouble(values.get(2)),
                            Double.parseDouble(values.get(3))
                    ));
                    movingPoint.setVelocityX(Double.parseDouble(values.get(4)));
                    movingPoint.setVelocityY(Double.parseDouble(values.get(5)));
                    movingPoint.setVelocityZ(Double.parseDouble(values.get(6)));

                    trajectories.add(movingPoint);
                } catch (NumberFormatException e) {
                    System.out.println("Invalid number in line: " + line);
                }
            }
        }

        return trajectories;
    }

    public static FileDetails extractFileDetails(String filePath) throws IOException {
        Set<Class<?>> dataTypes = findDataTypes(filePath);

        String fileExtension = getFileExtension(filePath);
        String format = (fileExtension.isEmpty()) ? "unknown" : fileExtension;

        StringBuilder contentBuilder = new StringBuilder();
        for (Class<?> dataType : dataTypes) {
            contentBuilder.append(dataType.getSimpleName()).append(" ");
        }

        String content = contentBuilder.toString().trim();

        return new FileDetails(filePath, format, content);
    }

    private static Set<Class<?>> findDataTypes(String filePath) throws IOException {
        Set<Class<?>> dataTypes = new HashSet<>();

        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] values = line.split("\\s+");

                for (String value : values) {
                    try {
                        Double.parseDouble(value);
                        dataTypes.add(Double.class);
                    } catch (NumberFormatException e) {
                        // Not a double, ignore for now
                    }
                }
            }
        }

        return dataTypes;
    }

    private static String getFileExtension(String filePath) {
        int lastDotIndex = filePath.lastIndexOf(".");
        if (lastDotIndex != -1) {
            return filePath.substring(lastDotIndex + 1);
        }
        return "";
    }
}
