int main(void)
{
    int TableSize = 10000; /* 散列表的估计大小 */
    int wordcount = 0, length;
    HashTable H;
    ElementType word;
    FILE *fp;
    char document[30] = "HarryPotter.txt"; /* 要被统计词频的文件名 */

    H = InitializeTable(TableSize); /* 建立散列表 */

    if ((fp = fopen(document, "r")) == NULL)
        FatalError("无法打开文件!\n");

    while (!feof(fp)) {
        length = GetAWord(fp, word); /* 从文件中读取一个单词 */
    
        if (length > 3) { /* 只考虑适当长度的单词 */
            wordcount++; /*统计文件中单词总数 */
            InsertAndCount(word, H);
        }
    }

    fclose( fp );

    printf("该文档共出现 %d 个有效单词，", wordcount);

    /*
     * (1)统计最大词频；
     * (2)用一组数统计从1到最大词频的单词数；
     * (3)计算前10%的词频应该是多少
     * (4)输出前10%词频的单词
     */
    Show(H, 10.0 / 100); /* 显示词频前10%的所有单词 */

    DestroyTable(H); /* 销毁散列表 */
    return 0;
}