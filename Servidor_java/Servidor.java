package Servidor_java;

import java.net.*;
import java.io.*;
import java.nio.*;

import java.util.Scanner;
import java.util.Properties;

import Servidor_java.Modelos.Celular;
import Servidor_java.Servicos.CatalogoCelular;
import Servidor_java.Servicos.GestorVendas;
import Servidor_java.Stream.PojoInputstream;

public class Servidor {
    public static void main(String args[]){
        System.out.println("Teste");
        
        Celular c1 = new Celular(1,"IPhone 15","Apple celular",5000.0,5,"Apple","15 Pro");
        Celular c2 = new Celular(2,"Poco 11","Celular xiaomi poco 11",5000.0,5,"Xiaomi","poco 11");

        CatalogoCelular catalogo_celular = new CatalogoCelular();

        catalogo_celular.adicionarCelular(c1);
        catalogo_celular.adicionarCelular(c2);


        try {

            //coletando as informações do host e porta do arquivo .properties
            Properties prop = new Properties();
            prop.load(new FileInputStream("Servidor_java/config.properties"));
            String host = prop.getProperty("server.host");
            int porta = Integer.parseInt(prop.getProperty("server.porta"));

            System.out.println("Servidor iniciado em " + host + " : " + porta);
            
            //iniciando o servidor
            ServerSocket server = new ServerSocket(porta);
            Socket cliente = server.accept();
            System.out.println("Cliente conectado: " + server.getInetAddress());

            
            //iniciando serialização
            InputStream entrada = cliente.getInputStream();
            PojoInputstream pojo_stream;
            
            byte[] buffer = new byte[4];
            entrada.read(buffer);
            
            int tamanho_pacote = ByteBuffer.wrap(buffer).order(ByteOrder.LITTLE_ENDIAN).getInt();
            System.out.println("Tamanho do pacote recebido: " + tamanho_pacote + " bytes");

            byte[] data_buffer = new byte[tamanho_pacote];
            entrada.read(data_buffer);


            pojo_stream = new PojoInputstream(new ByteArrayInputStream(data_buffer));
            int quantidade_produtos = pojo_stream.lerIntLE();

            System.out.println("Recebido " + quantidade_produtos + "Produtos");

            for(int i=0; i < quantidade_produtos; i++){
                Celular c = pojo_stream.lerCelular();
                catalogo_celular.adicionarCelular(c);
                System.out.println("Item " + (i+1) + " adicionado  no catalogo: " + c.getNome());
            }





            System.out.println("Conexão encerrada pelo cliente.");            
            cliente.close();

        } catch (FileNotFoundException e) {
            System.out.println("Erro: arquivo .properties nao encontrado");

        }catch (IOException e) {
           System.out.println("erro de IO no .properties");
        }catch (NumberFormatException e) {
            System.out.println("erro de formatação do .properties");
        }




    }
}

