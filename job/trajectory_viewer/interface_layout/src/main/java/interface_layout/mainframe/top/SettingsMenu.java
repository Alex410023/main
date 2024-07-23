package interface_layout.mainframe.top;

import javax.swing.JMenu;
import javax.swing.JMenuItem;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SettingsMenu extends JMenu {
    public SettingsMenu(String menuText, String[] options) {
        super(menuText);

        for (String option : options) {
            JMenuItem menuItem = new JMenuItem(option);
            menuItem.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    System.out.println("Option selected: " + option);
                }
            });
            add(menuItem);
        }
    }
}