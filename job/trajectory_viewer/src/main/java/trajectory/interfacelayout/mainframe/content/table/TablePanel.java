package trajectory.interfacelayout.mainframe.content.table;

import lombok.Getter;
import trajectory.interfacelayout.ErrorLogger;
import trajectory.interfacelayout.LabelPanel;
import trajectory.interfacelayout.mainframe.content.ContentPanel;
import trajectory.interfacelayout.mainframe.content.catalog.CatalogPanel;
import trajectory.interfacelayout.mainframe.content.file.FilePanel;
import trajectory.interfacelayout.mainframe.content.graph.GraphPanel;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.table.DefaultTableModel;
import javax.swing.JOptionPane;

import java.awt.BorderLayout;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.File;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * A panel that displays a table of trajectory data.
 */
public class TablePanel extends JPanel {
    @Getter
    private Table table;
    private CatalogPanel catalogPanel;
    private FilePanel filePanel;
    private GraphPanel graphPanel;
    private DefaultTableModel model;
    private int expectedListSize = 7;

    /**
     * Constructs a new {@link TablePanel} object.
     */
    public TablePanel() {
    }

    /**
     * Initializes the table panel with the specified content panel.
     *
     * @param contentPanel the content panel that contains the catalog panel, file panel, and graph panel
     */
    public void initTablePanel(ContentPanel contentPanel) {
        setLayout(new BorderLayout());
        this.catalogPanel = contentPanel.getCatalogPanel();
        this.filePanel = contentPanel.getFilePanel();
        this.graphPanel = contentPanel.getGraphPanel();

        LabelPanel tableLabel = new LabelPanel("Таблица");

        table = new Table(this);
        TableContextMenu contextMenu = new TableContextMenu(this);
        table.addMouseListener(contextMenu);

        model = table.getModel();

        add(tableLabel, BorderLayout.NORTH);
        JScrollPane scrollPane = new JScrollPane(table);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);

        add(scrollPane, BorderLayout.CENTER);
    }

    /**
     * Sets the edited flag for the selected file in the catalog panel.
     */
    public void setFileEdited() {
        catalogPanel.setFileEdited(true);
        filePanel.writeOnPanel(getTableStringData());
        graphPanel.getDrawPanel().updateTrajectories();
    }

    /**
     * Clears the table data.
     */
    public void clean() {
        model.setRowCount(0);
    }

    /**
     * Checks if a line of data is valid.
     *
     * @param line the line of data to check
     * @param lineNum the line number
     * @return true if the line is valid, false otherwise
     */
    private boolean isValidLine(String[] line, int lineNum) {
        List<String> listValues = new ArrayList<>(Arrays.asList(line));

        if (listValues.size() != expectedListSize) {
            String errorMessage = "Несовпадающая размерность строки №" + lineNum;
            ErrorLogger.logError(errorMessage);
            JOptionPane.showMessageDialog(
                    null,
                    errorMessage,
                    "Ошибка",
                    JOptionPane.ERROR_MESSAGE);
            return false;
        }

        for (String value : listValues) {
            if (!value.isEmpty() && !value.equalsIgnoreCase("nan")) {
                try {
                    Double.parseDouble(value);
                } catch (NumberFormatException e) {
                    String errorMessage = "В строке №" + lineNum + " присутствует не Double тип данных";
                    ErrorLogger.logError(errorMessage);
                    JOptionPane.showMessageDialog(
                            null,
                            errorMessage,
                            "Ошибка",
                            JOptionPane.ERROR_MESSAGE);
                    return false;
                }
            }
        }
        return true;
    }


    /**
     * Writes the data from a file to the table.
     *
     * @param file the file to read the data from
     */
    public void writeFileOnTable(File file) {
        if (table.isEditing()) {
            table.getCellEditor().stopCellEditing();
        }

        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            model.setRowCount(0);

            String line;
            int lineNum = 0;
            while ((line = br.readLine()) != null) {
                String[] values = line.split("\\s+");
                if (isValidLine(values, lineNum)) {
                    model.addRow(values);
                }
                lineNum++;
            }
            table.clearSelection();
        } catch (IOException e) {
            String errorMessage = "Ошибка при чтении файла: " + e.getMessage();
            ErrorLogger.logError(errorMessage);
            e.printStackTrace();
        }
    }

    /**
     * Returns the size of the table.
     *
     * @return the size of the table
     */
    public int getTableSize() {
        return table.getSize().height;
    }

    /**
     * Returns the data from the specified column in the table as an {@link ArrayList} of {@link Double} values.
     *
     * @param columnIndex the index of the column to retrieve data from
     * @return the data from the specified column as an {@link ArrayList} of {@link Double} values
     */
    public ArrayList<Double> getDataFromCol(int columnIndex) {
        ArrayList<Double> data = new ArrayList<>();

        if (columnIndex >= 0) {
            for (int i = 0; i < model.getRowCount(); i++) {
                Object value = model.getValueAt(i, columnIndex);
                if (value != null && !value.toString().isEmpty() &&
                        !value.toString().equalsIgnoreCase("nan")) {
                    data.add(Double.parseDouble(value.toString()));
                }
            }
        }

        return data;
    }


    /**
     * Returns the data from the table as a 2D {@link ArrayList} of {@link Double} values.
     *
     * @return the data from the table as a 2D {@link ArrayList} of {@link Double} values
     */
    public ArrayList<ArrayList<Double>> getTableData() {
        ArrayList<ArrayList<Double>> data = new ArrayList<>();

        for (int i = 0; i < model.getColumnCount(); i++) {
            data.add(getDataFromCol(i));
        }

        return data;
    }

    /**
     * Returns the data from the table as a {@link String} in a space-separated format.
     *
     * @return the data from the table as a {@link String} in a space-separated format
     */
    public String getTableStringData() {
        StringBuilder sb = new StringBuilder();

        ArrayList<ArrayList<Double>> data = getTableData();

        for (int i = 0; i < data.get(0).size(); i++) {
            for (int j = 0; j < data.size(); j++) {
                sb.append(data.get(j).get(i)).append(" ");
            }
            sb.append("\n");
        }

        return sb.toString();
    }
}