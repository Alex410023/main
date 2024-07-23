package interface_layout.mainframe.top.fileoptions;

import file_system.FileCatalog;
import interface_layout.mainframe.content.ContentPanel;
import interface_layout.mainframe.content.file.FilePanel;
import interface_layout.mainframe.content.table.TablePanel;

import javax.swing.JMenu;
import javax.swing.JMenuItem;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class CloseMenuItem extends JMenu {
    private FileCatalog fileCatalog;
    private FilePanel filePanel;
    private TablePanel tablePanel;
    public CloseMenuItem(ContentPanel contentPanel, FileCatalog fileCatalog) {
        super("Закрыть");

        this.fileCatalog = fileCatalog;
        this.filePanel = contentPanel.getFilePanel();
        this.tablePanel = contentPanel.getTablePanel();

        MouseAdapter mouseAdapter = new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                updateClose();
            }
        };

        addMouseListener(mouseAdapter);
    }

    private void updateClose() {
        this.removeAll();

        for (int i = 0; i < fileCatalog.getListModel().size(); i++) {
            final int index = i;
            String trajectoryName = fileCatalog.getListModel().getElementAt(index);
            JMenuItem menuItem = new JMenuItem(trajectoryName);

            menuItem.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    fileCatalog.deleteFromCatalog(index);
                    filePanel.writeOnPanel("");
                    tablePanel.clean();
                }
            });
            add(menuItem);
        }

        this.revalidate();
        this.repaint();
    }
}
