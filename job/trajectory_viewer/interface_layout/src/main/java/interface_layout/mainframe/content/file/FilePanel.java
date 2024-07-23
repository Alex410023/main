package interface_layout.mainframe.content.file;

import interface_layout.LabelPanel;

import java.awt.BorderLayout;
import java.awt.Dimension;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;
import javax.swing.JOptionPane;
import javax.swing.JFileChooser;
import javax.swing.event.DocumentListener;
import javax.swing.text.PlainDocument;
import javax.swing.event.DocumentEvent;

public class FilePanel extends JPanel {
    private LabelPanel fileLabel;
    private JTextArea textArea;

    private File fileWritten;
    private boolean textEdited;

    public FilePanel(int initWidth, int initHeight) {
        setLayout(new BorderLayout());
        setPreferredSize(new Dimension(initWidth, initHeight));

        fileLabel = new LabelPanel("Файл");
        textEdited = false;

        textArea = new JTextArea(20, 30);
        textArea.setEditable(true);
        textArea.setDocument(new PlainDocument());

        textArea.getDocument().addDocumentListener(new DocumentListener() {
            @Override
            public void insertUpdate(DocumentEvent e) {
                textEdited = true;
            }

            @Override
            public void removeUpdate(DocumentEvent e) {
                textEdited = true;
            }

            @Override
            public void changedUpdate(DocumentEvent e) {
                textEdited = true;
            }
        });

        JScrollPane scrollPane = new JScrollPane(textArea);

        add(fileLabel, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
    }

    public void handleEditedFile(File file) {
        if (textEdited) {
            Object[] options = {"Да", "Нет", "Отмена"};
            int option = JOptionPane.showOptionDialog(null,
                    "Присутствуют несохраненные изменения. Хотите сохранить их?",
                    "Несохраненные изменения",
                    JOptionPane.YES_NO_CANCEL_OPTION,
                    JOptionPane.QUESTION_MESSAGE,
                    null,
                    options,
                    options[0]);

            if (option == JOptionPane.YES_OPTION) {
                saveAsNew();
                writeFileOnPanel(file);
            } else if (option == JOptionPane.NO_OPTION) {
                revertChanges();
            }
        }
    }

    public void writeFileOnPanel(File file) {
        textArea.setEditable(true);

        try {
            String fileContent = readFileContent(file);
            textArea.setText(fileContent);
            fileWritten = file;
            textEdited = false;
        } catch (IOException ex) {
            showErrorDialog("Error reading file: " + ex.getMessage());
        }
    }

    private void revertChanges() {
        try {
            textArea.setText(readFileContent(fileWritten));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        textEdited = false;
    }

    private void showErrorDialog(String errorMessage) {
        JOptionPane.showMessageDialog(this, errorMessage, "Error", JOptionPane.ERROR_MESSAGE);
    }

    private void saveAsNew() {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setDialogTitle("Сохранить файл");
        fileChooser.setApproveButtonText("Сохранить");

        int userSelection = fileChooser.showSaveDialog(this);

        if (userSelection == JFileChooser.APPROVE_OPTION) {
            File fileToSave = fileChooser.getSelectedFile();

            try (FileWriter fileWriter = new FileWriter(fileToSave)) {
                fileWriter.write(textArea.getText());
                textEdited = false;
                JOptionPane.showMessageDialog(null, "Файл успешно сохранён.");
            } catch (IOException e) {
                JOptionPane.showMessageDialog(null, "Ошибка при сохранении файла: " + e.getMessage(), "Ошибка", JOptionPane.ERROR_MESSAGE);
            }
        }

        textEdited = false;
    }

    private String readFileContent(File file) throws IOException {
        StringBuilder content = new StringBuilder();
        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = br.readLine())!= null) {
                content.append(line).append("\n");
            }
        }
        return content.toString();
    }

    public void writeOnPanel(String text) {
        textArea.setText(text);
    }

    public boolean isEdited() {
        return textEdited;
    }
}
