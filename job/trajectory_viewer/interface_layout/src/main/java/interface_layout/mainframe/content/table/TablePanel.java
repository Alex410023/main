package interface_layout.mainframe.content.table;

import interface_layout.LabelPanel;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.table.DefaultTableModel;
import javax.swing.JOptionPane;

import java.awt.BorderLayout;
import java.awt.Dimension;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.File;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class TablePanel extends JPanel {
    private LabelPanel tableLabel;
    private Table table;

    public TablePanel(int initWidth, int initHeight) {
        setLayout(new BorderLayout());
        setPreferredSize(new Dimension(initWidth, initHeight));

        tableLabel = new LabelPanel("Таблица");

        table = new Table();

        add(tableLabel, BorderLayout.NORTH);
        JScrollPane scrollPane = new JScrollPane(table);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);

        add(scrollPane, BorderLayout.CENTER);
    }

    public void clean() {
        DefaultTableModel model = table.getModel();
        model.setRowCount(0);
    }

    private boolean isValidLine(String[] line, int lineNum) {
        List<String> listValues = new ArrayList<>(Arrays.asList(line));
        if (listValues.size() != 7) {
            JOptionPane.showMessageDialog(
                    null,
                    "Несовпадающая размерность строки №" + lineNum,
                    "Ошибка",
                    JOptionPane.ERROR_MESSAGE);
            return false;
        }

        for (String value : listValues) {
            if (!value.isEmpty() && !value.equalsIgnoreCase("nan")) {
                try {
                    Double.parseDouble(value);
                } catch (NumberFormatException e) {
                    JOptionPane.showMessageDialog(
                            null,
                            "В строке №" + lineNum + "присутствует не Double тип данных",
                            "Ошибка",
                            JOptionPane.ERROR_MESSAGE);
                    return false;
                }
            }
        }
        return true;
    }

    public void writeFileOnTable(File file) {
        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            DefaultTableModel model = table.getModel();

            model.setRowCount(0);

            String line;
            int lineNum = 0;
            while ((line = br.readLine()) != null) {
                String[] values = line.split("\\s+");
                if (isValidLine(values, lineNum)) {
                    model.addRow(values);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}