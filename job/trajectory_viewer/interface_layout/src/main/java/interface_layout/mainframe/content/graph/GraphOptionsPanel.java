package interface_layout.mainframe.content.graph;

import java.awt.FlowLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JPanel;

public class GraphOptionsPanel extends JPanel {
    public GraphOptionsPanel() {
        setLayout(new FlowLayout(FlowLayout.LEFT));

        setPreferredSize(new Dimension(getWidth(), 35));

        JButton button1 = new JButton("Найти");
        button1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("'Найти' button pressed");
            }
        });
        add(button1);

        JButton button2 = new JButton("Удалить");
        button2.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("'Удалить' button pressed");
            }
        });
        add(button2);
    }
}