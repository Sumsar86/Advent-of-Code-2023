import java.io.File;
import java.io.FileNotFoundException;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import java.util.Set;
import java.util.stream.Collectors;

public class Main {
    static List<String> readFile(String file_name) {
        List<String> lines = new ArrayList<>();
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
        return lines;
    }

    public static void main(String[] args) {
        String faili_nimi = "sis.txt";
        List<String> read = readFile(faili_nimi);
        List<Mang> mangud = new ArrayList<Mang>();

        int summa = 0;
        for (String r : read) {
            Mang mang = new Mang(r);
            mangud.add(mang);

            for (int tegelik : mang.tegelikud_num) {
                if (mang.voidu_num.contains(tegelik))
                    mang.voitude_arv++;
            }
            if (mang.voitude_arv != 0)
                summa += Math.pow(2, mang.voitude_arv - 1);
        }
        
        System.out.println("1.1: " + summa);

        summa = 0;
        for (int i = 0; i < mangud.size(); i++) {
            summa += mangud.get(i).koopiate_arv;
            for (int j = 1; j <= mangud.get(i).voitude_arv; j++) {
                // System.out.println(i + " " + (i + j));
                if (i + j < mangud.size())
                    mangud.get(i + j).koopiate_arv += mangud.get(i).koopiate_arv;
            }
            // System.out.println(mangud.get(i));
        }

        System.out.println("1.2: " + summa);
    }
}

class Mang {
    int num, koopiate_arv, voitude_arv;
    Set<Integer> voidu_num, tegelikud_num;

    Mang(String mang) {
        List<String> osad = split(mang, Arrays.asList(':', '|'));
        num = Integer.parseInt(split(osad.get(0), ' ').get(1));
        koopiate_arv = 1; // koos iseendaga
        voitude_arv = 0;
        voidu_num = split(osad.get(1), ' ').stream().map(Integer::parseInt).collect(Collectors.toSet());
        tegelikud_num = split(osad.get(2), ' ').stream().map(Integer::parseInt).collect(Collectors.toSet());
    }

    @Override
    public String toString() {
        return num + " (" + koopiate_arv + ", " + voitude_arv + "): " + voidu_num + ", " + tegelikud_num;
    }

    static List<String> split(String line, List<Character> delimiters) {
        List<String> pieces = new ArrayList<String>();
        StringBuilder sb = new StringBuilder();
        for (char c : line.toCharArray()) {
            if (delimiters.contains(c)) {
                if (sb.length() > 0)
                    pieces.add(sb.toString());
                sb.setLength(0);
                continue;
            }
            sb.append(c);
        }
        if (sb.length() > 0)
            pieces.add(sb.toString());
        return pieces;
    }

    static List<String> split(String line, char delimiter) {
        List<String> pieces = new ArrayList<String>();
        StringBuilder sb = new StringBuilder();
        for (char c : line.toCharArray()) {
            if (c == delimiter) {
                if (sb.length() > 0)
                    pieces.add(sb.toString());
                sb.setLength(0);
                continue;
            }
            sb.append(c);
        }
        if (sb.length() > 0)
            pieces.add(sb.toString());
        return pieces;
    }
}