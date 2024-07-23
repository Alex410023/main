package data_model;

public class FileDetails {
    private String path;
    private String format;
    private String content;

    public FileDetails() {
    }

    public FileDetails(String path, String format, String content) {
        this.path = path;
        this.format = format;
        this.content = content;
    }

    public String getPath() {
        return path;
    }

    public void setPath(String path) {
        this.path = path;
    }

    public String getFormat() {
        return format;
    }

    public void setFormat(String format) {
        this.format = format;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }
}
