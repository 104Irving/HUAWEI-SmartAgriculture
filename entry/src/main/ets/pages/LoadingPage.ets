@Entry
@Component

struct LoadingPage{
  @State message: string = '少女祈祷中......'
  build(){
    Row(){
      Column(){
        Text(this.message)
          .fontSize(42)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Green)
      }
      .width('100%')
    }
    .height('100%')
  }
}