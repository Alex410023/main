package interface_layout.mainframe.top;

import file_system.FileCatalog;
import interface_layout.mainframe.content.ContentPanel;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;

import javax.swing.JMenuBar;
import javax.swing.JPanel;

public class TopPanel extends JPanel {
    public TopPanel(ContentPanel contentPanel, FileCatalog fileCatalog, int initWidth) {
        setPreferredSize(new Dimension(initWidth, 40));
        setBackground(new Color(106, 153, 208));

        setLayout(new FlowLayout(FlowLayout.LEFT));


//        String[] fileOptions = {"Открыть", "Открыть недавние", "Закрыть", "Закрыть все"};
        String[] settingsOptions = {"Сохранить положение окон"};

        JMenuBar menuBar = new JMenuBar();

        FileMenu fileTopPanel = new FileMenu(contentPanel, fileCatalog,"Файл");
        SettingsMenu settingsTopPanel = new SettingsMenu("Настройки", settingsOptions);

        menuBar.add(fileTopPanel);
        menuBar.add(settingsTopPanel);

        menuBar.setPreferredSize(new Dimension(145, 30));

        add(menuBar);
    }
}