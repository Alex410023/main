package trajectory.interfacelayout.mainframe.content.table;


import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPopupMenu;
import javax.swing.SwingUtilities;
import javax.swing.table.DefaultTableModel;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;

/**
 * A context menu for the table that allows inserting and deleting rows, and displaying statistics.
 */
class TableContextMenu extends MouseAdapter {
    private final TablePanel tablePanel;
    private final Table table;
    private final DefaultTableModel model;

    /**
     * Constructs a new {@link TableContextMenu} object with the specified {@link TablePanel}.
     *
     * @param tablePanel the {@link TablePanel} that contains the table
     */
    public TableContextMenu(TablePanel tablePanel) {
        this.tablePanel = tablePanel;
        this.table = tablePanel.getTable();
        this.model = table.getModel();
    }

    /**
     * Shows the context menu when the user right-clicks on a cell in the table.
     *
     * @param e the mouse event that triggered the method call
     */
    @Override
    public void mousePressed(MouseEvent e) {
        if (SwingUtilities.isRightMouseButton(e)) {
            int row = table.rowAtPoint(e.getPoint());
            int col = table.columnAtPoint(e.getPoint());

            if (row >= 0 && col >= 0) {
                table.setRowSelectionInterval(row, row);
                table.setColumnSelectionInterval(col, col);
            }

            JPopupMenu popupMenu = new JPopupMenu();
            JMenuItem insertAboveItem = new JMenuItem("Добавить строку сверху");
            JMenuItem insertBelowItem = new JMenuItem("Добавить строку снизу");
            JMenuItem deleteItem = new JMenuItem("Удалить строку");
            JMenuItem statsItem = new JMenuItem("Отобразить статистику");

            insertAboveItem.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    insertRow(true);
                    tablePanel.setFileEdited();
                }
            });

            insertBelowItem.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    insertRow(false);
                    tablePanel.setFileEdited();
                }
            });

            deleteItem.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    deleteRow();
                    tablePanel.setFileEdited();
                }
            });

            statsItem.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    displayStatistics();
                }
            });

            popupMenu.add(insertAboveItem);
            popupMenu.add(insertBelowItem);
            popupMenu.add(deleteItem);
            popupMenu.add(statsItem);

            popupMenu.show(e.getComponent(), e.getX(), e.getY());
        }
    }

    /**
     * Inserts a new row above or below the selected row in the table.
     *
     * @param above true if the new row should be inserted above the selected row, false if it should be inserted below
     */
     void insertRow(boolean above) {
        int row = table.getSelectedRow();
        if (row < 0) {
            return;
        }

        int newRow = above ? row : row + 1;
        Object[] newRowData = new Object[model.getColumnCount()];

        if (newRow > 0 && newRow < model.getRowCount()) {
            for (int col = 0; col < model.getColumnCount(); col++) {
                double upperValue = Double.parseDouble(model.getValueAt(newRow - 1, col).toString());
                double lowerValue = Double.parseDouble(model.getValueAt(newRow, col).toString());
                double newValue = (upperValue + lowerValue) / 2;
                newRowData[col] = newValue < 0.0 ? 0.0 : (double) Math.round(newValue * 1000) / 1000;
            }
        } else if (newRow == 0) {
            for (int col = 0; col < model.getColumnCount(); col++) {
                double lowerValue = Double.parseDouble(model.getValueAt(newRow, col).toString());
                double newValue = lowerValue - 1;
                newRowData[col] = newValue < 0.0 ? 0.0 : (double) Math.round(newValue * 1000) / 1000;
            }
        } else {
            for (int col = 0; col < model.getColumnCount(); col++) {
                double upperValue = Double.parseDouble(model.getValueAt(newRow - 1, col).toString());
                double newValue = upperValue + 1;
                newRowData[col] = newValue < 0.0 ? 0.0 : (double) Math.round(newValue * 1000) / 1000;
            }
        }

        model.insertRow(newRow, newRowData);
    }

    /**
     * Deletes the selected row from the table.
     */
     void deleteRow() {
        int row = table.getSelectedRow();
        if (row < 0) {
            return;
        }

        model.removeRow(row);
    }

    /**
     * Displays statistics for the table data.
     */
    private void displayStatistics() {
        ArrayList<ArrayList<Double>> data = tablePanel.getTableData();
        StringBuilder statsText = new StringBuilder();

        for (int i = 1; i < data.size(); i++) {
            ArrayList<Double> columnData = data.get(i);
            String columnName = table.getColumnName(i);

            double average = StatisticsCalculator.calculateAverage(columnData);
            double variance = StatisticsCalculator.calculateVariance(columnData, average);
            double secondMoment = StatisticsCalculator.calculateSecondMoment(columnData, average);
            double thirdMoment = StatisticsCalculator.calculateThirdMoment(columnData, average);

            statsText.append(columnName).append(":\n");
            statsText.append("Среднее: ").append(String.format("%.3f", average)).append("\n");
            statsText.append("Дисперсия: ").append(String.format("%.3f", variance)).append("\n");
            statsText.append("Выборочный момент второго порядка: ").append(String.format("%.3f", secondMoment)).append("\n");
            statsText.append("Выборочный момент третьего порядка: ").append(String.format("%.3f", thirdMoment)).append("\n\n");
        }

        JOptionPane.showMessageDialog(null, statsText.toString(), "Статистика", JOptionPane.INFORMATION_MESSAGE);
    }
}