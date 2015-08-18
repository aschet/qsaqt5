connect(listView, "itemClicked(QListWidgetItem*)", clicked);

var clickCount = 0;

function clicked(item)
{
    if (item)
        item.text = "Item clicked %1".arg(clickCount++);
}
