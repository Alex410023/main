package trajectory.interfacelayout.mainframe.content.table;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.mockito.Mockito;
import trajectory.interfacelayout.mainframe.content.ContentPanel;

import java.lang.reflect.Method;

import java.util.Arrays;
import java.util.Random;

public class TableFilterTest {
    private TablePanel tablePanel;

    @Before
    public void setup() {
        ContentPanel contentPanel = Mockito.mock(ContentPanel.class);

        tablePanel = new TablePanel();
        tablePanel.initTablePanel(contentPanel);
    }

    @Test
    public void testSortTableRows_baseTable_equals() {
        tablePanel.getTable().getModel().addRow(new Object[] {2.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0});
        tablePanel.getTable().getModel().addRow(new Object[] {1.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0});
        tablePanel.getTable().getModel().addRow(new Object[] {3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0});

        tablePanel.getTable().sortTableRows();

        Assert.assertEquals(1.0, tablePanel.getTable().getModel().getValueAt(0, 0));
        Assert.assertEquals(2.0, tablePanel.getTable().getModel().getValueAt(1, 0));
        Assert.assertEquals(3.0, tablePanel.getTable().getModel().getValueAt(2, 0));
    }

    @Test
    public void testSortTableRows_duplicateValues_equals() {
        tablePanel.getTable().getModel().addRow(new Object[]{3.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0});
        tablePanel.getTable().getModel().addRow(new Object[]{1.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0});
        tablePanel.getTable().getModel().addRow(new Object[]{1.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0});

        tablePanel.getTable().sortTableRows();

        Assert.assertEquals(1.0, tablePanel.getTable().getModel().getValueAt(0, 0));
        Assert.assertEquals(1.0, tablePanel.getTable().getModel().getValueAt(1, 0));
        Assert.assertEquals(3.0, tablePanel.getTable().getModel().getValueAt(2, 0));
    }

    @Test
    public void testSortTableRows_emptyTable_isEmpty() {
        tablePanel.getTable().sortTableRows();

        Assert.assertTrue(tablePanel.getTable().getModel().getRowCount() == 0);
    }

    @Test
        public void testSortTableRows_largeTable_equals() {
        int size = 10000;
        Random random = new Random();
        double[] times = new double[10000];
        for (int i = 0; i < times.length; i++) {
            times[i] = random.nextDouble() * 1000;
            tablePanel.getTable().getModel().addRow(new Object[]{times[i], i, i, i, i, i, i});
        }

        long startTime = System.currentTimeMillis();

        tablePanel.getTable().sortTableRows();

        long endTime = System.currentTimeMillis();
        long elapsedTime = endTime - startTime;

        System.out.println("Таблица размером " + size + " строк отсортирована за " + elapsedTime + " мс");

        Arrays.sort(times);
        for (int i = 0; i < times.length; i++) {
            Assert.assertEquals(times[i], tablePanel.getTable().getModel().getValueAt(i, 0));
        }
    }
}