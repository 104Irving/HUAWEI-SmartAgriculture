package com.qdong.back;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.FileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;
import org.apache.tomcat.util.http.fileupload.disk.DiskFileItemFactory;

import java.io.File;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.List;

@WebServlet(name = "UploadUserPicture", value = "/UploadUserPicture")
public class UploadServlet extends HttpServlet {
    private static final String CHARSET = "UTF-8";
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException, UnsupportedEncodingException {
        req.setCharacterEncoding(CHARSET);
        if (ServletFileUpload.isMultipartContent((javax.servlet.http.HttpServletRequest) req)) {
            File tempFile = new File(req.getSession().getServletContext().getRealPath("/") + "temp");
            if (!tempFile.exists()) tempFile.mkdirs();

            DiskFileItemFactory factory = new DiskFileItemFactory();
            factory.setSizeThreshold(1024 * 1024 * 10);
            factory.setRepository(tempFile);

            ServletFileUpload upload = new ServletFileUpload((FileItemFactory) factory);
            upload.setHeaderEncoding(CHARSET);

            File uploadFile = new File(req.getSession().getServletContext().getRealPath("/") + "UserPicTure");
            if (!uploadFile.exists()) uploadFile.mkdirs();

            try {
                List<FileItem> fileItems =  upload.parseRequest((javax.servlet.http.HttpServletRequest) req);
                for (FileItem item : fileItems) {
                    if (item.isFormField()) {
                        String name = item.getFieldName();
                        String value = item.getString(CHARSET);
                        System.out.println("name: " + name + ", value: " + value);
                    } else {
                        String fileName = item.getName();
                        File file = new File(uploadFile, fileName);
                        item.write(file);
                        System.out.println(fileName + ", file length: " + file.length());
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
