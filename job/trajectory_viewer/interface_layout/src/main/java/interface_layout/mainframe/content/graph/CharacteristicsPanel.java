package interface_layout.mainframe.content.graph;

import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.Box;
import javax.swing.JPanel;
import java.awt.FlowLayout;
import java.awt.Dimension;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;


import lombok.Data;

@Data
public class CharacteristicsPanel extends JPanel {
    private JCheckBox xCheckBox;
    private JCheckBox yCheckBox;
    private JCheckBox zCheckBox;
    private JCheckBox xVCheckBox;
    private JCheckBox yVCheckBox;
    private JCheckBox zVCheckBox;

    public CharacteristicsPanel() {
        setLayout(new FlowLayout(FlowLayout.LEFT));

        setPreferredSize(new Dimension(getWidth(), 35));

        JLabel label1 = new JLabel("Координаты:");
        add(label1);

        xCheckBox = new JCheckBox("X, м");
        xCheckBox.addItemListener(new CheckBoxListener());
        add(xCheckBox);

        yCheckBox = new JCheckBox("Y, м");
        yCheckBox.addItemListener(new CheckBoxListener());
        add(yCheckBox);

        zCheckBox = new JCheckBox("Z, м");
        zCheckBox.addItemListener(new CheckBoxListener());
        add(zCheckBox);

        add(Box.createRigidArea(new Dimension(100, 0)));

        JLabel label2 = new JLabel("Проекции скорости:");
        add(label2);

        xVCheckBox = new JCheckBox("Vx, м/с");
        xVCheckBox.addItemListener(new CheckBoxListener());
        add(xVCheckBox);

        yVCheckBox = new JCheckBox("Vy, м/с");
        yVCheckBox.addItemListener(new CheckBoxListener());
        add(yVCheckBox);

        zVCheckBox = new JCheckBox("Vz, м/с");
        zVCheckBox.addItemListener(new CheckBoxListener());
        add(zVCheckBox);
    }

    private class CheckBoxListener implements ItemListener {
        @Override
        public void itemStateChanged(ItemEvent e) {
            JCheckBox checkBox = (JCheckBox) e.getSource();
            if (checkBox.isSelected()) {
                if (checkBox == xCheckBox || checkBox == yCheckBox || checkBox == zCheckBox) {
                    xVCheckBox.setSelected(false);
                    yVCheckBox.setSelected(false);
                    zVCheckBox.setSelected(false);
                } else {
                    xCheckBox.setSelected(false);
                    yCheckBox.setSelected(false);
                    zCheckBox.setSelected(false);
                }
            }
        }
    }
}