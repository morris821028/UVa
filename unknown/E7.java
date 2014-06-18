package ce1002.E7.s100502205;

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;

public class E7 extends JFrame {
	public JList list;
	public JTextField txtInput;
	public JButton btnAdd;
	public JButton btnOrder;
	private JScrollPane scrollPane;
	public DefaultListModel listModel;

	public E7() {
		this.setTitle("E7");
		this.setSize(500, 500);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setResizable(false);
		this.setLayout(new GridBagLayout());

		listModel = new DefaultListModel();
		list = new JList(listModel);
		txtInput = new JTextField();
		btnAdd = new JButton("add");
		btnOrder = new JButton("Order");
		scrollPane = new JScrollPane(list);

		int[] px = { 0, 0, 1, 1, 2, 3 };
		int[] py = { 0, 3, 0, 3, 3, 3 };
		int[] wx = { 1, 1, 4, 1, 1, 1 };
		int[] wy = { 3, 2, 3, 2, 2, 2 };
		Object[] obj = { new JLabel("Menu"), new JLabel("Add new item:"),
				scrollPane, txtInput, btnAdd, btnOrder };
		for (int i = 0; i < px.length; i++) {
			GridBagConstraints GBC = new GridBagConstraints();
			GBC.insets = new Insets(10, 10, 10, 10);
			GBC.fill = GridBagConstraints.HORIZONTAL;
			GBC.anchor = GridBagConstraints.EAST;
			GBC.gridx = py[i];
			GBC.gridy = px[i];
			GBC.gridwidth = wy[i];
			GBC.gridheight = wx[i];
			this.add((Component) obj[i], GBC);
		}
		list.addMouseListener(new MouseAdapter() {
				@Override
				public void mouseClicked(MouseEvent e) {
					if(e.getClickCount() == 2) {
						int idx = list.locationToIndex(e.getPoint());
						Object item = listModel.getElementAt(idx);
						String text = JOptionPane.showInputDialog("Rename " + item);
						if(text.trim().equals(""))
							return;
						listModel.remove(idx);
						addItem(text);
					}
				}
		});
		btnAdd.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (txtInput.getText().trim().equals(""))
					return;
				addItem(txtInput.getText().trim());
			}
		});
		btnOrder.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				printList();
			}
		});

		this.setVisible(true);
	}

	public void addItem(String str) {
		for (int i = 0; i < listModel.size(); i++) {
			if (listModel.get(i).equals(str))
				return;
		}
		listModel.addElement(str);
		txtInput.setText("");
	}

	public void printList() {
		int[] Idx = list.getSelectedIndices();
		for (int x : Idx) {
			System.out.println(listModel.get(x));
		}
	}

	public static void main(String[] args) {
		new E7();
	}

}
