package Servidor_java;

import java.net.*;
import java.io.*;

import java.util.Properties;

import Servidor_java.Modelos.Capa;
import Servidor_java.Modelos.Celular;
import Servidor_java.Modelos.Pelicula;
import Servidor_java.Modelos.PowerBank;
import Servidor_java.Servicos.CatalogoProdutos;

import Servidor_java.Serializacao.RequestReply;

import Servidor_java.Utils.FileOutputStream_catalogo;

public class Servidor {

    public static void main(String args[]){
        
        CatalogoProdutos catalogo_Geral = new CatalogoProdutos();

        catalogo_Geral.AdicionarProduto(new Celular(1,"IPhone 15","Apple celular",5000.0,5,"Apple","15 Pro"));
        catalogo_Geral.AdicionarProduto(new Capa(2, "Capa Iphone", "Capa de cor azul", 15, 20, "Iphone 15", "Plastico"));
        catalogo_Geral.AdicionarProduto(new Pelicula(3, "Pelicula","5 polegadas" , 25.50, 15, "Iphone 15", "Vidro Temperado"));
        catalogo_Geral.AdicionarProduto(new PowerBank(4,"Power Bank","Bateria Retangular",200.0,10,"Xiaomi","10000mAh",1000));
    
        ServerSocket server = null;

        try {
            
            Properties prop = new Properties();
            prop.load(new FileInputStream("Servidor_java/config.properties"));
            
            String host = prop.getProperty("server.host");
            int porta = Integer.parseInt(prop.getProperty("server.porta"));

            System.out.println("Servidor iniciado em " + host + " : " + porta);

            server = new ServerSocket(porta);

            for(;;){
                
                try {

                    System.out.println("Aguardando conexões.");            
                    Socket cliente = server.accept();
                    System.out.println("Cliente conectado: " + server.getInetAddress());
                    
                    boolean conexaoAtiva = true;
                    while (conexaoAtiva) {
                        try {
                            
                            RequestReply requisicao = new RequestReply(cliente.getInputStream(), cliente.getOutputStream());
                            int operacao = requisicao.obterOperacao();
                            
                            if (operacao == -1) {break;}
                            
                            requisicao.processarRequisicao(catalogo_Geral, operacao);

                            FileOutputStream_catalogo.salvarCatalogoCsv(catalogo_Geral);
                        
                        } catch (IOException e) {
                            conexaoAtiva = false;
                            System.out.println("Cliente desconectado: " + e.getMessage());

                        }
                    }
                   
                    System.out.println("Conexão encerrada pelo cliente.");            
                    cliente.close();

                } catch (IOException e) {
                    System.out.println("Erro ao processar cliente: " + e.getMessage());
                    e.printStackTrace();
                }
            }

        } catch (FileNotFoundException e) {
            System.out.println("Erro: arquivo .properties nao encontrado");

        }catch (IOException e) {
           System.out.println("erro de IO no .properties");
        }catch (NumberFormatException e) {
            System.out.println("erro de formatação do .properties");
        }finally {
            System.out.println("Servidor encerrado.");
        }




    }
}

