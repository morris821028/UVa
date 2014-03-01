import java.io.*;
import java.text.*;

//
// File:    practice.java
// Purpose: practice program, sigma positive integers 
// Author:  pc2@ecs.csus.edu or http://www.ecs.csus.edu/pc2
// 
// Thu Jul 03 16:03:50 2003
// 
// $HeadURL: http://pc2.ecs.csus.edu/repos/pc2v9/branches/PC2_RELEASE_9_1_x/samps/practice.java $
// 

public class practice {
	public static void main(String[] args)
	{
		try
		{
			RandomAccessFile file = new RandomAccessFile("practice.in", "r");
			String line;

			int inval = 0;
			int sum = 0;

			while ((line = file.readLine()) != null)
			{
				inval = new Integer(line.trim()).intValue();
				sum = 0;

				if (inval == 0)
					System.exit(0);

				if (inval < 1)
				{
					for (int i = 1; i >= inval; i--)
						sum += i;
				}
				else
				{
					for (int i = 1; i <= inval; i++)
						sum += i;
				}
				System.out.println("N = " + inval + "  Sum = " + sum);
			}

			System.out.println("Did not find trailing zero");
		}
		catch (Exception e)
		{
			System.out.println("Possible trouble reading practice.in");
		}
		System.exit(4);
	}
}

// eof practice.java $Id: practice.java 543 2007-05-03 18:32:47Z laned $
