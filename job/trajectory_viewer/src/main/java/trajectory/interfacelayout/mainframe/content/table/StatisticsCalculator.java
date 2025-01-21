package trajectory.interfacelayout.mainframe.content.table;

import java.util.ArrayList;

/**
 * A utility class for calculating statistical measures of a dataset.
 */
public class StatisticsCalculator {
    /**
     * Calculates the average of a dataset.
     *
     * @param data the dataset
     * @return the average of the dataset
     */
    public static double calculateAverage(ArrayList<Double> data) {
        double sum = 0;
        for (double value : data) {
            sum += value;
        }
        return sum / data.size();
    }

    /**
     * Calculates the variance of a dataset.
     *
     * @param data the dataset
     * @param average the average of the dataset
     * @return the variance of the dataset
     */
    public static double calculateVariance(ArrayList<Double> data, double average) {
        double sum = 0;
        for (double value : data) {
            sum += Math.pow(value - average, 2);
        }
        return sum / data.size();
    }

    /**
     * Calculates the second moment of a dataset.
     *
     * @param data the dataset
     * @param average the average of the dataset
     * @return the second moment of the dataset
     */
    public static double calculateSecondMoment(ArrayList<Double> data, double average) {
        double sum = 0;
        for (double value : data) {
            sum += Math.pow(value, 2);
        }
        return sum / data.size();
    }

    /**
     * Calculates the third moment of a dataset.
     *
     * @param data the dataset
     * @param average the average of the dataset
     * @return the third moment of the dataset
     */
    public static double calculateThirdMoment(ArrayList<Double> data, double average) {
        double sum = 0;
        for (double value : data) {
            sum += Math.pow(value, 3);
        }
        return sum / data.size();
    }
}