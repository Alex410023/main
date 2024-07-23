package interface_layout.mainframe.content.catalog;

import interface_layout.LabelPanel;
import interface_layout.mainframe.content.file.FilePanel;
import file_system.FileCatalog;
import interface_layout.mainframe.content.table.TablePanel;

import java.awt.BorderLayout;
import java.awt.Dimension;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import java.io.File;


public class CatalogPanel extends JPanel {
    private LabelPanel labelPanel;

    public CatalogPanel(FilePanel filePanel, TablePanel tablePanel, FileCatalog fileCatalog, int initWidth, int initHeight) {
        setLayout(new BorderLayout());
        setPreferredSize(new Dimension(initWidth, initHeight));

        labelPanel = new LabelPanel("Каталог");

        fileCatalog.getFileNameList().addListSelectionListener(new ListSelectionListener() {
            @Override
            public void valueChanged(ListSelectionEvent e) {
                if (!e.getValueIsAdjusting()) {
                    int selectedIndex = fileCatalog.getFileNameList().getSelectedIndex();
                    if (selectedIndex >= 0) {
                        filePanel.writeFileOnPanel(fileCatalog.getFileList().get(selectedIndex));
                        tablePanel.writeFileOnTable(fileCatalog.getFileList().get(selectedIndex));
                    } else {
                        filePanel.writeOnPanel("");
                        tablePanel.clean();
                    }
                }
            }
        });

        JScrollPane scrollPane = fileCatalog.getFileListScrollPane();

        add(labelPanel, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
    }
}