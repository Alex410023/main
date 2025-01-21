package trajectory.interfacelayout.mainframe.content.table;

import lombok.Getter;
import trajectory.interfacelayout.ErrorLogger;

import javax.swing.AbstractCellEditor;
import javax.swing.JTable;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.JLabel;
import javax.swing.table.TableCellEditor;
import javax.swing.JTextField;

import java.awt.Color;
import java.awt.Component;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

/**
 * A custom {@link JTable} implementation for the trajectory viewer project.
 * This table allows editing of decimal numbers and sorts the rows based on the time column.
 */
public class Table extends JTable {
    @Getter
    private final DefaultTableModel model;
    private final TablePanel tablePanel;
    private final String[] columnIdentifiers = {"T, c", "X, м", "Y, м", "Z, м", "Vx, м/с", "Vy, м/с", "Vz, м/с"};
    
    /**
     * Constructs a new {@link Table} object with the specified {@link TablePanel}.
     *
     * @param tablePanel the {@link TablePanel} that contains this table
     */
    public Table(TablePanel tablePanel) {
        super();
        this.tablePanel = tablePanel;
        model = new DefaultTableModel(columnIdentifiers, 0);
        setModel(model);
        getTableHeader().setReorderingAllowed(false);

        for (int i = 0; i < getColumnCount(); i++) {
            getColumn(getColumnName(i)).setCellRenderer(new CenteredCellRenderer());
        }

        DecimalNumberEditor decimalNumberEditor = new DecimalNumberEditor();
        for (int i = 0; i < getColumnCount(); i++) {
            getColumn(getColumnName(i)).setCellEditor(decimalNumberEditor);
        }
    }

    /**
     * A custom {@link DefaultTableCellRenderer} that centers the text in the table cells.
     */
    private static class CenteredCellRenderer extends DefaultTableCellRenderer {
        @Override
        public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected,
                                                       boolean hasFocus, int row, int column) {
            JLabel label = (JLabel) super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);
            label.setHorizontalAlignment(JLabel.CENTER);
            return label;
        }
    }

    /**
     * Sorts the rows of the table based on the time column.
     * This method is called when the user edits a cell in the time column.
     */
    void sortTableRows() {
        List<Object[]> rows = new ArrayList<>();
        for (int i = 0; i < model.getRowCount(); i++) {
            Object[] rowData = new Object[model.getColumnCount()];
            for (int j = 0; j < model.getColumnCount(); j++) {
                rowData[j] = model.getValueAt(i, j);
            }
            rows.add(rowData);
        }

        rows.sort(Comparator.comparing(o -> Double.parseDouble(o[0].toString())));

        for (int i = 0; i < rows.size(); i++) {
            for (int j = 0; j < model.getColumnCount(); j++) {
                model.setValueAt(rows.get(i)[j], i, j);
            }
        }
    }

    /**
     * A custom {@link TableCellEditor} that allows editing of decimal numbers in the table cells.
     */
    private class DecimalNumberEditor extends AbstractCellEditor implements TableCellEditor {
        private final JTextField textField;
        private Object oldValue;
        private boolean isValid = true;

        /**
         * Constructs a new {@link DecimalNumberEditor} object.
         */
        public DecimalNumberEditor() {
            textField = new JTextField();
            textField.setHorizontalAlignment(JTextField.CENTER);
            textField.getDocument().addDocumentListener(new DocumentListener() {
                @Override
                public void insertUpdate(DocumentEvent e) {
                    validateInput();
                }

                @Override
                public void removeUpdate(DocumentEvent e) {
                    validateInput();
                }

                @Override
                public void changedUpdate(DocumentEvent e) {
                    validateInput();
                }
            });
        }

        /**
         * Returns the component used for editing the table cell.
         *
         * @param table the table being edited
         * @param value the value of the table cell
         * @param isSelected true if the cell is selected
         * @param row the row of the cell being edited
         * @param column the column of the cell being edited
         * @return the component used for editing the table cell
         */
        @Override
        public Component getTableCellEditorComponent(JTable table, Object value, boolean isSelected, int row, int column) {
            oldValue = value;
            textField.setText(value == null ? "" : value.toString());
            return textField;
        }

        /**
         * Returns the value of the table cell being edited.
         *
         * @return the value of the table cell being edited
         */
        @Override
        public Object getCellEditorValue() {
            if (isValid) {
                return textField.getText();
            } else {
                return oldValue;
            }
        }

        /**
         * Stops editing the table cell and saves the changes.
         *
         * @return true if the editing was stopped successfully
         */
        @Override
        public boolean stopCellEditing() {
            if (isValid) {
                String newValue = textField.getText();
                if (!newValue.equals(oldValue.toString())) {
                    model.setValueAt(newValue, getEditingRow(), getEditingColumn());

                    if (getEditingColumn() == 0) { // if the time edited column is the Time column
                        sortTableRows();
                        // since the edited cell sets the user's value to the cell
                        textField.setText(model.getValueAt(editingRow, editingColumn).toString());
                    }
                    tablePanel.setFileEdited();
                }

                return super.stopCellEditing();
            } else {
                textField.setBackground(Color.RED);
                return false;
            }
        }

        /**
         * Cancels editing the table cell and restores the original value.
         */
        @Override
        public void cancelCellEditing() {
            super.cancelCellEditing();
            textField.setBackground(Color.WHITE);
        }

        /**
         * Validates the input in the table cell being edited.
         */
        private void validateInput() {
            String text = textField.getText();
            try {
                double value = Double.parseDouble(text);
                int column = getEditingColumn();
                if ((column == 0 || column >= 4) && value < 0.0) {
                    isValid = false;
                    textField.setBackground(Color.RED);
                    String errorMessage = "Некорректное значение: " + text + " в столбце " + column;
                    ErrorLogger.logError(errorMessage);
                } else {
                    isValid = true;
                    textField.setBackground(Color.WHITE);
                }
            } catch (NumberFormatException e) {
                isValid = false;
                textField.setBackground(Color.RED);
                String errorMessage = "Некорректный формат числа: " + text;
                ErrorLogger.logError(errorMessage);
            }
        }
    }
}