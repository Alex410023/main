package interface_layout.mainframe.content.table;

import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.JLabel;

import java.awt.Component;

public class Table extends JTable {
    private DefaultTableModel model;

    public Table() {
        super();
        model = createTableModel();
        setModel(model);

        for (int i = 0; i < getColumnCount(); i++) {
            getColumn(getColumnName(i)).setCellRenderer(new CenteredCellRenderer());
        }
    }

    private DefaultTableModel createTableModel() {
//        DefaultTableModel model = new DefaultTableModel();
        String[] columnIdentifiers = {"T, c", "X, м", "Y, м", "Z, м", "Vx, м/с", "Vy, м/с", "Vz, м/с"};
        return new NonEditableTableModel(columnIdentifiers, 0);
    }

    public DefaultTableModel getModel() {
        return model;
    }

    private static class CenteredCellRenderer extends DefaultTableCellRenderer {
        @Override
        public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected,
                                                       boolean hasFocus, int row, int column) {
            JLabel label = (JLabel) super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);
            label.setHorizontalAlignment(JLabel.CENTER);
            return label;
        }
    }

    private static class NonEditableTableModel extends DefaultTableModel {
        public NonEditableTableModel(Object[] columnNames, int rowCount) {
            super(columnNames, rowCount);
        }

        @Override
        public boolean isCellEditable(int row, int column) {
            return false;
        }
    }
}
