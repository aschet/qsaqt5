connect(listView, "itemClicked(QListWidgetItem*)", changed);

function changed(item)
{
    if (item) {
        var color_name = item.text;
        var color = new Color(color_name);
        var palette = listView.palette();
        var active = palette.active;
        active.base = color;
        active.highlight = color.dark();
        palette.active = active;
        listView.setPalette(palette);
    }
}

