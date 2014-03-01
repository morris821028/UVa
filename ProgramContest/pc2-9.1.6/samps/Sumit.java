import java.io.RandomAccessFile;

/**
 * sum the integers in the file sumit.dat.
 * 
 * @author pc2@ecs.csus.edu
 */

// $HeadURL: http://pc2.ecs.csus.edu/repos/pc2v9/branches/PC2_RELEASE_9_1_x/samps/Sumit.java $
public class Sumit {

    public void doSum(String filename) {
        try {
            RandomAccessFile file = new RandomAccessFile(filename, "r");
            String line;
            int sum = 0;
            int rv = 0;
            while ((line = file.readLine()) != null) {
                rv = new Integer(line.trim()).intValue();
                if (rv > 0) {
                    sum = sum + rv;
                    // System.out.println(line);
                }
            }
            System.out.print("The sum of the integers is " + sum);
        } catch (Exception e) {
            System.out.println("Possible trouble reading Sumit.dat");
        }
    }

    public static void main(String[] args) {

        new Sumit().doSum("sumit.dat");

    }
}

// eof Sumit.java $Id: Sumit.java 210 2007-04-14 06:55:17Z laned $
