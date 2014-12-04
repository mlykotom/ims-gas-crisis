/*
 * Java utilita vytvorena pro projekt do predmetu IMS (VIT - FIT).
 * Ma za ukol samplovat a prumerovat data pred vykreslenim programem gnuplot.
 */
package datasampler;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Matej Marecek, xmarec12@stud.fit.vutbr.cz
 */
public class DataSampler {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        if(args.length < 2){
            System.out.println("Zadejte cestu k souboru, sampling[int].\n"
                    + "Pocet sloupcu bude automaticky detekovat, je-li soubor validni a sloupce oddeleny tabulatorem");
            System.exit(1);
        }
        try {
            BufferedReader in = new BufferedReader(new FileReader(args[0]));
            String strLine;
            int sampling = Integer.parseInt(args[1]);
            int counter = 0;
            ArrayList<Double> columsArray = new ArrayList<Double>();

            while ((strLine = in.readLine()) != null)   {
                if(strLine.startsWith("#")){
                    System.out.println(strLine);
                    continue;
                }
                if(counter < sampling){
                    String[] split = strLine.split("\t");
                    for (int i = 0; i < split.length; i++) {
                        Double newValue = Double.parseDouble(split[i]);
                        if(columsArray.size() < (i+1)){
                            columsArray.add(new Double(0.0));
                        }
                        Double get = columsArray.get(i);
                        get += newValue;
                        columsArray.set(i, get);
                    }
                    counter++;
                }
                else{
                    for (int i = 0; i < columsArray.size(); i++) {
                        System.out.print(columsArray.get(i)/(double)sampling + "\t");
                    }
                    System.out.println("");
                    counter = 0;
                    columsArray.clear();
                }
            }
        } catch (Exception ex) {
            Logger.getLogger(DataSampler.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
