package trajectory.interfacelayout.mainframe.content.table;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.mockito.Mockito;
import trajectory.interfacelayout.mainframe.content.ContentPanel;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class RowInsertionTest {
    private TableContextMenu tableContextMenu;
    private TablePanel tablePanel;

    @Before
    public void setup() {
        ContentPanel contentPanel = Mockito.mock(ContentPanel.class);

        tablePanel = new TablePanel();
        tablePanel.initTablePanel(contentPanel);
        tableContextMenu = new TableContextMenu(tablePanel);

        tablePanel.getTable().getModel().addRow(new Object[] {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0});
        tablePanel.getTable().getModel().addRow(new Object[] {2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0});
    }

    @Test
    public void testInsertRowAbove_positive_equals() {
        tablePanel.getTable().setRowSelectionInterval(1, 1);

        tableContextMenu.insertRow(true);

        Assert.assertEquals(1.5, tablePanel.getTable().getModel().getValueAt(1, 0));
        Assert.assertEquals(2.5, tablePanel.getTable().getModel().getValueAt(1, 1));
        Assert.assertEquals(3.5, tablePanel.getTable().getModel().getValueAt(1, 2));
        Assert.assertEquals(4.5, tablePanel.getTable().getModel().getValueAt(1, 3));
        Assert.assertEquals(5.5, tablePanel.getTable().getModel().getValueAt(1, 4));
        Assert.assertEquals(6.5, tablePanel.getTable().getModel().getValueAt(1, 5));
        Assert.assertEquals(7.5, tablePanel.getTable().getModel().getValueAt(1, 6));
    }

    @Test
    public void testInsertRowBelow_positive_equals() {
        tablePanel.getTable().setRowSelectionInterval(0, 0);

        tableContextMenu.insertRow(false);

        Assert.assertEquals(1.5, tablePanel.getTable().getModel().getValueAt(1, 0));
        Assert.assertEquals(2.5, tablePanel.getTable().getModel().getValueAt(1, 1));
        Assert.assertEquals(3.5, tablePanel.getTable().getModel().getValueAt(1, 2));
        Assert.assertEquals(4.5, tablePanel.getTable().getModel().getValueAt(1, 3));
        Assert.assertEquals(5.5, tablePanel.getTable().getModel().getValueAt(1, 4));
        Assert.assertEquals(6.5, tablePanel.getTable().getModel().getValueAt(1, 5));
        Assert.assertEquals(7.5, tablePanel.getTable().getModel().getValueAt(1, 6));
    }

    @Test
    public void testInsertRowAtTop_positive_equals() {
        tablePanel.getTable().setRowSelectionInterval(0, 0);

        tableContextMenu.insertRow(true);

        Assert.assertEquals(1.0, tablePanel.getTable().getModel().getValueAt(1, 0));
        Assert.assertEquals(2.0, tablePanel.getTable().getModel().getValueAt(1, 1));
        Assert.assertEquals(3.0, tablePanel.getTable().getModel().getValueAt(1, 2));
        Assert.assertEquals(4.0, tablePanel.getTable().getModel().getValueAt(1, 3));
        Assert.assertEquals(5.0, tablePanel.getTable().getModel().getValueAt(1, 4));
        Assert.assertEquals(6.0, tablePanel.getTable().getModel().getValueAt(1, 5));
        Assert.assertEquals(7.0, tablePanel.getTable().getModel().getValueAt(1, 6));
    }

    @Test
    public void testInsertRowAtBottom_positive_equals() {
        tablePanel.getTable().setRowSelectionInterval(1, 1);

        tableContextMenu.insertRow(false);

        Assert.assertEquals(2.0, tablePanel.getTable().getModel().getValueAt(1, 0));
        Assert.assertEquals(3.0, tablePanel.getTable().getModel().getValueAt(1, 1));
        Assert.assertEquals(4.0, tablePanel.getTable().getModel().getValueAt(1, 2));
        Assert.assertEquals(5.0, tablePanel.getTable().getModel().getValueAt(1, 3));
        Assert.assertEquals(6.0, tablePanel.getTable().getModel().getValueAt(1, 4));
        Assert.assertEquals(7.0, tablePanel.getTable().getModel().getValueAt(1, 5));
        Assert.assertEquals(8.0, tablePanel.getTable().getModel().getValueAt(1, 6));
    }

    @Test
    public void testInsertRowAbove_negative_equals() {
        tablePanel.clean();
        tablePanel.getTable().getModel().addRow(new Object[] {1.0, 2.0, -3.0, 4.0, -5.0, 6.0, -7.0});
        tablePanel.getTable().getModel().addRow(new Object[] {2.0, -3.0, 4.0, -5.0, 6.0, -7.0, 8.0});

        tablePanel.getTable().setRowSelectionInterval(1, 1);

        tableContextMenu.insertRow(true);
    }
}