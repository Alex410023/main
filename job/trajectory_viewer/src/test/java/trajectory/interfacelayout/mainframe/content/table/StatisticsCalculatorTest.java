package trajectory.interfacelayout.mainframe.content.table;

import org.junit.Assert;
import org.junit.Test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

public class StatisticsCalculatorTest {
    @Test
    public void testCalculateAverage_positiveValues_equals() {
        ArrayList<Double> data = new ArrayList<>(Arrays.asList(1.0, 2.0, 3.0, 4.0, 5.0));
        double average = StatisticsCalculator.calculateAverage(data);
        Assert.assertEquals(3.0, average, 0.001);
    }

    @Test
    public void testCalculateVariance_positiveValues_equals() {
        ArrayList<Double> data = new ArrayList<>(Arrays.asList(1.0, 2.0, 3.0, 4.0, 5.0));
        double average = StatisticsCalculator.calculateAverage(data);
        double variance = StatisticsCalculator.calculateVariance(data, average);
        Assert.assertEquals(2.0, variance, 0.001);
    }

    @Test
    public void testCalculateSecondMoment_positiveValues_equals() {
        ArrayList<Double> data = new ArrayList<>(Arrays.asList(1.0, 2.0, 3.0, 4.0, 5.0));
        double average = StatisticsCalculator.calculateAverage(data);
        double secondMoment = StatisticsCalculator.calculateSecondMoment(data, average);
        Assert.assertEquals(11.0, secondMoment, 0.001);
    }

    @Test
    public void testCalculateThirdMoment_positiveValues_equals() {
        ArrayList<Double> data = new ArrayList<>(Arrays.asList(1.0, 2.0, 3.0, 4.0, 5.0));
        double average = StatisticsCalculator.calculateAverage(data);
        double thirdMoment = StatisticsCalculator.calculateThirdMoment(data, average);
        Assert.assertEquals(45.0, thirdMoment, 0.001);
    }


    @Test
    public void testCalculateAverage_negativeValues_equals() {
        ArrayList<Double> data = new ArrayList<>(Arrays.asList(-1.0, 2.0, -3.0, 4.0, -5.0));
        double average = StatisticsCalculator.calculateAverage(data);
        Assert.assertEquals(-0.6, average, 0.001);
    }

    @Test
    public void testCalculateVariance_negativeValues_equals() {
        ArrayList<Double> data = new ArrayList<>(Arrays.asList(-1.0, 2.0, -3.0, 4.0, -5.0));
        double average = StatisticsCalculator.calculateAverage(data);
        double variance = StatisticsCalculator.calculateVariance(data, average);
        Assert.assertEquals(10.64, variance, 0.001);
    }

    @Test
    public void testCalculateSecondMoment_negativeValues_equals() {
        ArrayList<Double> data = new ArrayList<>(Arrays.asList(-1.0, 2.0, -3.0, 4.0, -5.0));
        double average = StatisticsCalculator.calculateAverage(data);
        double secondMoment = StatisticsCalculator.calculateSecondMoment(data, average);
        Assert.assertEquals(11.0, secondMoment, 0.001);
    }

    @Test
    public void testCalculateThirdMoment_negativeValues_equals() {
        ArrayList<Double> data = new ArrayList<>(Arrays.asList(-1.0, 2.0, -3.0, 4.0, -5.0));
        double average = StatisticsCalculator.calculateAverage(data);
        double thirdMoment = StatisticsCalculator.calculateThirdMoment(data, average);
        Assert.assertEquals(-16.2, thirdMoment, 0.001);
    }


    @Test
    public void testCalculateAverage_emptyDataset_isNaN() {
        ArrayList<Double> data = new ArrayList<>();
        double average = StatisticsCalculator.calculateAverage(data);
        Assert.assertTrue(Double.isNaN(average));
    }

    @Test
    public void testCalculateVariance_emptyDataset_isNaN() {
        ArrayList<Double> data = new ArrayList<>();
        double average = StatisticsCalculator.calculateAverage(data);
        double variance = StatisticsCalculator.calculateVariance(data, average);
        Assert.assertTrue(Double.isNaN(variance));
    }

    @Test
    public void testCalculateSecondMoment_emptyDataset_isNaN() {
        ArrayList<Double> data = new ArrayList<>();
        double average = StatisticsCalculator.calculateAverage(data);
        double secondMoment = StatisticsCalculator.calculateSecondMoment(data, average);
        Assert.assertTrue(Double.isNaN(secondMoment));
    }

    @Test
    public void testCalculateThirdMoment_emptyDataset_isNaN() {
        ArrayList<Double> data = new ArrayList<>();
        double average = StatisticsCalculator.calculateAverage(data);
        double thirdMoment = StatisticsCalculator.calculateThirdMoment(data, average);
        Assert.assertTrue(Double.isNaN(thirdMoment));
    }

    @Test
    public void testCalculateAverage_largeDataset_getTime() {
        int size = 1_000_000;
        ArrayList<Double> data = new ArrayList<>(size);
        Random random = new Random();
        for (int i = 0; i < size; i++) {
            data.add(random.nextDouble() * 100);
        }

        long startTime = System.currentTimeMillis();
        double average = StatisticsCalculator.calculateAverage(data);
        long endTime = System.currentTimeMillis();
        long elapsedTime = endTime - startTime;

        System.out.println("Вычислено среднее " + size + " значений за " + elapsedTime + " мс");
    }

    @Test
    public void testCalculateVariance_largeDataset_getTime() {
        int size = 1_000_000;
        ArrayList<Double> data = new ArrayList<>(size);
        Random random = new Random();
        for (int i = 0; i < size; i++) {
            data.add(random.nextDouble() * 100);
        }

        double average = StatisticsCalculator.calculateAverage(data);

        long startTime = System.currentTimeMillis();
        double variance = StatisticsCalculator.calculateVariance(data, average);
        long endTime = System.currentTimeMillis();
        long elapsedTime = endTime - startTime;

        System.out.println("Вычислена дисперсия " + size + " значений за " + elapsedTime + " мс");
    }

    @Test
    public void testCalculateSecondMoment_largeDataset_getTime() {
        int size = 1_000_000;
        ArrayList<Double> data = new ArrayList<>(size);
        Random random = new Random();
        for (int i = 0; i < size; i++) {
            data.add(random.nextDouble() * 100);
        }

        double average = StatisticsCalculator.calculateAverage(data);

        long startTime = System.currentTimeMillis();
        double secondMoment = StatisticsCalculator.calculateSecondMoment(data, average);
        long endTime = System.currentTimeMillis();
        long elapsedTime = endTime - startTime;

        System.out.println("Вычислен момент второго порядка " + size + " значений за " + elapsedTime + " мс");
    }

    @Test
    public void testCalculateThirdMoment_largeDataset_getTime() {
        int size = 1_000_000;
        ArrayList<Double> data = new ArrayList<>(size);
        Random random = new Random();
        for (int i = 0; i < size; i++) {
            data.add(random.nextDouble() * 100);
        }

        double average = StatisticsCalculator.calculateAverage(data);

        long startTime = System.currentTimeMillis();
        double thirdMoment = StatisticsCalculator.calculateThirdMoment(data, average);
        long endTime = System.currentTimeMillis();
        long elapsedTime = endTime - startTime;

        System.out.println("Вычислен момент третьего порядка " + size + " значений за " + elapsedTime + " мс");
    }
}