package Servidor_java;

import java.net.*;
import java.io.*;
import java.nio.*;

import java.util.Properties;

import Servidor_java.Modelos.Celular;

import Servidor_java.Servicos.CatalogoCelular;
import Servidor_java.Servicos.GestorVendas;

import Servidor_java.Stream.PojoInputstream;
import Servidor_java.Stream.PojoOutputStream;

import Servidor_java.Serializacao.Request;

import Servidor_java.Utils.FileOutputStream_catalogo;

public class Servidor {

    public static void main(String args[]){
        
        CatalogoCelular catalogo_celular = new CatalogoCelular();
        catalogo_celular.adicionarCelular(new Celular(1,"IPhone 15","Apple celular",5000.0,5,"Apple","15 Pro"));
        catalogo_celular.adicionarCelular(new Celular(2,"Poco 11","Celular xiaomi poco 11",5000.0,5,"Xiaomi","poco 11"));
    
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
                            
                            Request requisicao = new Request(cliente.getInputStream(), cliente.getOutputStream());
                            int operacao = requisicao.obterOperacao();
                            
                            if (operacao == -1) {break;}
                            
                            requisicao.processarRequisicao(catalogo_celular, operacao);

                            FileOutputStream_catalogo.salvarCatalogo(catalogo_celular);
                            FileOutputStream_catalogo.salvarCatalogoCsv(catalogo_celular);
                        
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

