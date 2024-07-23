package interface_layout.mainframe.top.fileoptions;

import file_system.FileCatalog;
import interface_layout.mainframe.content.ContentPanel;
import interface_layout.mainframe.content.file.FilePanel;
import interface_layout.mainframe.content.table.TablePanel;

import javax.swing.JMenuItem;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class CloseAllMenuItems extends JMenuItem {
    private FilePanel filePanel;
    private TablePanel tablePanel;
    public CloseAllMenuItems(ContentPanel contentPanel, FileCatalog fileCatalog) {
        super("Закрыть все");

        this.filePanel = contentPanel.getFilePanel();
        this.tablePanel = contentPanel.getTablePanel();

        ActionListener listener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                while (!fileCatalog.getFileList().isEmpty()) {
                    fileCatalog.deleteFromCatalog(0);
                    filePanel.writeOnPanel("");
                    tablePanel.clean();
                }
                update();
            }
        };

        addActionListener(listener);
    }

    private void update() {
        this.removeAll();
        this.revalidate();
        this.repaint();
    }
}
