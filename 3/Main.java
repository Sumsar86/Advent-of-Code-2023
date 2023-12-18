import java.io.File;  // Import the File class
import java.io.FileNotFoundException;  // Import this class to handle errors
import java.util.ArrayList;
// import java.util.Arrays;
import java.util.List;
import java.util.Scanner; // Import the Scanner class to read text files
// import java.util.HashSet;
// import java.util.Set;


public class Main {
    static void readFile(String file_name, List<String> lines) {
        try {
            File myObj = new File(file_name);
            Scanner myReader = new Scanner(myObj);
            while (myReader.hasNextLine()) {
                String data = myReader.nextLine();
                lines.add(data);
            }
            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    public static void extractNumbersFromMixedStrings(List<String> mixedStringList, List<Number> numbrid, List<Mark> margid) {
        // Set<Character> symbols = new HashSet<>(Arrays.asList('*', '#', '+', '$'));
        for (int rida = 0; rida < mixedStringList.size(); rida++) {
            StringBuilder numericPart = new StringBuilder();
            String mixedString = mixedStringList.get(rida);

            for (int veerg = 0; veerg < mixedString.length(); veerg++) {
                char character = mixedString.charAt(veerg);
                if (Character.isDigit(character)) {
                    numericPart.append(character);
                } else if (numericPart.length() > 0) {
                    // We found a non-digit character after a numeric part
                    try {
                        int number = Integer.parseInt(numericPart.toString());
                        numbrid.add(new Number(number, rida, veerg - numericPart.length(), veerg - 1));
                        numericPart.setLength(0); // Reset the numeric part
                    } catch (NumberFormatException e) {
                        System.err.println("Error converting string to number: " + numericPart);
                        numericPart.setLength(0); // Reset the numeric part
                    }
                    if (character != '.') {
                        margid.add(new Mark(character, rida, veerg, veerg));
                    }
                } else if (character != '.') {
                    margid.add(new Mark(character, rida, veerg, veerg));
                }
            }

            // Check if there is a numeric part at the end of the string
            int veerg = mixedString.length() - 1;
            if (numericPart.length() == 1 && numericPart.charAt(0) != '.') {
                margid.add(new Mark(numericPart.charAt(0), rida, veerg, veerg));
                numericPart.setLength(0);
            }
            if (numericPart.length() > 0) {
                try {
                    int number = Integer.parseInt(numericPart.toString());
                    numbrid.add(new Number(number, rida, veerg - numericPart.length(), veerg - 1));
                } catch (NumberFormatException e) {
                    System.err.println("Error converting string to number: " + numericPart);
                }
            }
        }
    }

    public static void main(String[] args) {
        String nimi = "sis.txt";
        List<String> read = new ArrayList<>();
        readFile(nimi, read);

        // for (String r : read) {
        //     System.out.println(r);
        // }

        List<Number> numbrid = new ArrayList<>();
        List<Mark> margid = new ArrayList<>();
        extractNumbersFromMixedStrings(read, numbrid, margid);

        for (Number n : numbrid) {
            for (Mark m : margid) {
                n.kasOnMootoriosa(m);
            }
        }

        int summa = 0;
        for (Number n : numbrid) {
            if (n.mootoriosa) {
                summa += n.num;
            }
            // System.out.printf("%s - %s\n", n.num, n.mootoriosa);
        }
        System.out.println("1.1: " + summa);

        summa = 0;
        for (Mark m : margid) {
            if (m.naabrid == 2) {
                summa += m.ylekandetegur;
            }
        }
        System.out.println("1.2: " + summa);
    }
}

abstract class Symbol {
    int rida;
    int algus;
    int lopp;
}

class Number extends Symbol {
    int num;
    boolean mootoriosa = false;

    public Number(int num, int rida, int algus, int lopp) {
        this.num = num;
        this.rida = rida;
        this.algus = algus;
        this.lopp = lopp;
    }

    public boolean kasOnMootoriosa(Mark s) {
        if (algus <= s.algus + 1 && lopp >= s.algus - 1
                && (rida == s.rida || rida == s.rida - 1 || rida == s.rida + 1)) {
            mootoriosa = true;
            if (s.mark == '*' && s.naabrid < 2) {
                s.naabrid++;
                s.ylekandetegur *= num;
            }
        }
        return mootoriosa;
    }
}

class Mark extends Symbol {
    char mark;
    int naabrid = 0;
    int ylekandetegur = 1;

    public Mark(char mark, int rida, int algus, int lopp) {
        this.mark = mark;
        this.rida = rida;
        this.algus = algus;
        this.lopp = lopp;
    }
}
