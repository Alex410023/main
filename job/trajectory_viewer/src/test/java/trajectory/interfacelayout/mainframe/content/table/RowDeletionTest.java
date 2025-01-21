package trajectory.interfacelayout.mainframe.content.table;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.mockito.Mockito;
import trajectory.interfacelayout.mainframe.content.ContentPanel;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class RowDeletionTest {
    private TableContextMenu tableContextMenu;
    private TablePanel tablePanel;

    @Before
    public void setup() {
        ContentPanel contentPanel = Mockito.mock(ContentPanel.class);

        tablePanel = new TablePanel();
        tablePanel.initTablePanel(contentPanel);
        tableContextMenu = new TableContextMenu(tablePanel);
    }

    @Test
    public void testDeleteFirstRow_multipleRowsTable_equals() {
        tablePanel.getTable().getModel().addRow(new Object[] {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0});
        tablePanel.getTable().getModel().addRow(new Object[] {2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0});

        tablePanel.getTable().setRowSelectionInterval(0, 0);

        tableContextMenu.deleteRow();

        Assert.assertEquals(2.0, tablePanel.getTable().getModel().getValueAt(0, 0));
        Assert.assertEquals(3.0, tablePanel.getTable().getModel().getValueAt(0, 1));
        Assert.assertEquals(4.0, tablePanel.getTable().getModel().getValueAt(0, 2));
        Assert.assertEquals(5.0, tablePanel.getTable().getModel().getValueAt(0, 3));
        Assert.assertEquals(6.0, tablePanel.getTable().getModel().getValueAt(0, 4));
        Assert.assertEquals(7.0, tablePanel.getTable().getModel().getValueAt(0, 5));
        Assert.assertEquals(8.0, tablePanel.getTable().getModel().getValueAt(0, 6));
    }

    @Test
    public void testDeleteLastRow_multipleRowsTable_equals() {
        tablePanel.getTable().getModel().addRow(new Object[] {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0});
        tablePanel.getTable().getModel().addRow(new Object[] {2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0});

        tablePanel.getTable().setRowSelectionInterval(1, 1);

        tableContextMenu.deleteRow();

        Assert.assertEquals(1.0, tablePanel.getTable().getModel().getValueAt(0, 0));
        Assert.assertEquals(2.0, tablePanel.getTable().getModel().getValueAt(0, 1));
        Assert.assertEquals(3.0, tablePanel.getTable().getModel().getValueAt(0, 2));
        Assert.assertEquals(4.0, tablePanel.getTable().getModel().getValueAt(0, 3));
        Assert.assertEquals(5.0, tablePanel.getTable().getModel().getValueAt(0, 4));
        Assert.assertEquals(6.0, tablePanel.getTable().getModel().getValueAt(0, 5));
        Assert.assertEquals(7.0, tablePanel.getTable().getModel().getValueAt(0, 6));
    }

    @Test
    public void testDeleteRow_singleRowTable_isEmpty() {
        tablePanel.getTable().getModel().addRow(new Object[] {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0});

        tablePanel.getTable().setRowSelectionInterval(0, 0);

        tableContextMenu.deleteRow();

        Assert.assertTrue(tablePanel.getTable().getModel().getRowCount() == 0);
    }

    @Test
    public void testDeleteRow_emptyTable_isEmpty() {
        tableContextMenu.deleteRow();

        Assert.assertTrue(tablePanel.getTable().getModel().getRowCount() == 0);
    }
}