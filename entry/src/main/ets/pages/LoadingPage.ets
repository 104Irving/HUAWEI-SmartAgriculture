@Entry
@Component

struct LoadingPage{
  @State message: string = '少女祈祷中......'
  build(){
    Row(){
      Column(){
        Text(this.message)
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)

        LoadingProgress()
          .color(Color.Blue)
          .height(100)
          .width(100)
      }
      .width('100%')
    }
    .height('100%')
  }
}