package hw_calendar;
import javax.swing.*;

public class Calendar_Month {
    private static final String[] calWeek = {"Sun","Mon","Tue","Wed","Thu","Fri",
                                            "Sat"};
    private static final String[] calMonth = {"January","February","March",
                                            "April","May","June","July",
                                            "August","September","October",
                                            "November","December"};
    private static final int[] oneMonth = {31,28,31,30,31,30,31,31,30,31,30,31};
    private static final int oneWeek = 7;
    private static final int oneYear = 12;
    private int thisYear;
    private int thisMonth;
    
    public void setYear(int year){
        thisYear = year;
    }

    public void setMonth(int month){
        thisMonth = month;
    }

    public int getYear(){
        return thisYear;
    }

    public int getMonth(){
        return thisMonth;
    }

    public String getMonthName(){
        return calMonth[getMonth()-1];
    }

    private int getFirstDay(){
        int firstday = (thisYear-1)*365 + (thisYear-1)/4 - (thisYear-1)/100
                + (thisYear-1)/400;
        for(int i=0; i < thisMonth-1; i++)
            firstday += oneMonth[i];
        firstday %= oneWeek;
        return firstday;
    }

    private int getLastDay(int month){
        if(month == 2)
            if(getYear()%4==0 && getYear()%100!=0 || getYear()%400==0)
                return oneMonth[1]+1;
            else
                return oneMonth[1];
        else
            return oneMonth[month-1];
    }

    public JTable tableMonth(){
        Object[][] data = {
            {null,null,null,null,null,null,null},
            {null,null,null,null,null,null,null},
            {null,null,null,null,null,null,null},
            {null,null,null,null,null,null,null},
            {null,null,null,null,null,null,null},
            {null,null,null,null,null,null,null}
        };

        for(int incDay = 1, firstday = getFirstDay();
                incDay <= getLastDay(getMonth()); incDay++)
            data[(firstday+incDay)/oneWeek][(firstday+incDay)%oneWeek] = incDay;
        JTable table = new JTable(data,calWeek);
        table.setSize(100, 100);
        return table;
    }

    public void showMonth(){
        JFrame frameCalendar =new JFrame();
        JScrollPane panel = new JScrollPane(tableMonth());
        frameCalendar.setTitle(calMonth[getMonth()-1]);
        frameCalendar.setBounds(300,250,300,155);
        frameCalendar.getContentPane().add(panel,"Center");
        frameCalendar.setVisible(true);
    }
}