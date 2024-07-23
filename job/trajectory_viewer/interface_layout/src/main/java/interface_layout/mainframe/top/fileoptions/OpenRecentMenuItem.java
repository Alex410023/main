package interface_layout.mainframe.top.fileoptions;

import file_system.FileCatalog;
import interface_layout.mainframe.content.ContentPanel;
import interface_layout.mainframe.content.file.FilePanel;

import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;


import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class OpenRecentMenuItem extends JMenu {
    private FileCatalog fileCatalog;
    private FilePanel filePanel;
    public OpenRecentMenuItem(ContentPanel contentPanel, FileCatalog fileCatalog) {
        super("Открыть недавние");

        this.fileCatalog = fileCatalog;
        this.filePanel = contentPanel.getFilePanel();

        MouseAdapter mouseAdapter = new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                updateRecent();
            }
        };

        addMouseListener(mouseAdapter);
    }

    private void updateRecent() {
        this.removeAll();

        for (int i = 0; i < fileCatalog.getFullListModel().size(); i++) {
            int index = i;
            String trajectoryName = fileCatalog.getFullListModel().getElementAt(i);
            JMenuItem menuItem = new JMenuItem(trajectoryName);

            menuItem.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    if (!fileCatalog.contains(fileCatalog.getFullFileList().get(index))) {
                        fileCatalog.addToCatalog(fileCatalog.getFullFileList().get(index),
                                fileCatalog.getFullListModel().getElementAt(index));
                    } else if (filePanel.isEdited()) {
                        filePanel.handleEditedFile(fileCatalog.getFullFileList().get(index));
                    } else {
                        JOptionPane.showMessageDialog(null, "Файл уже открыт");
                    }
                }
            });
            add(menuItem);
        }

        this.revalidate();
        this.repaint();
    }
}