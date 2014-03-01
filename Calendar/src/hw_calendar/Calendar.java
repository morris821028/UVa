package hw_calendar;
import javax.swing.*;

public class Calendar {
    private int format,col,row;
    private int thisYear;
    private static final int oneYear = 12;
    public Calendar_Month[] m = new Calendar_Month[12];

    Calendar(){
        for(int i=0;i<oneYear;++i)
            m[i] = new Calendar_Month();
    }

    public void setFormat(int format){
        if(format == 1){
            this.format=format;
            row = 4;
            col = 3;
        }
        else if(format == 2){
            this.format=format;
            row = 6;
            col = 2;
        }
    }
    public void setYear(int year){
        thisYear = year;
    }
    public int getYear(){
        return thisYear;
    }

    public void showYear(){
        JScrollPane[] pane = new JScrollPane[12];
        JTabbedPane[] tab = new JTabbedPane[12];
        JFrame frameCalendar =new JFrame();
        frameCalendar.setLayout(null);
        frameCalendar.setTitle(String.valueOf(getYear()));

        if(format == 1)
            frameCalendar.setBounds(200,100,840,660);
        else if(format == 2)
            frameCalendar.setBounds(200,50,570,970);

        for(int i=0; i < oneYear; ++i){
            m[i].setYear(getYear());
            m[i].setMonth(i+1);
            pane[i] = new JScrollPane(m[i].tableMonth());
            tab[i] = new JTabbedPane();
            tab[i].add(pane[i]);
            tab[i].setTitleAt(0, m[i].getMonthName());
            frameCalendar.add(tab[i]);
        }

        for(int x=0; x < row; ++x)
            for(int y=0; y < col; ++y)
                tab[x*col+y].setBounds(y*270+15, x*150+15, 250, 147);

        frameCalendar.setVisible(true);
    }
}