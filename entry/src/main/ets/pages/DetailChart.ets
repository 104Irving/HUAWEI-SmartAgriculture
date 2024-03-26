//显示该农田某一项数据具体信息及时间轴图标的页面
import router from '@ohos.router'

const name = router.getParams();


@Entry
@Component
struct DetailChart{
  build(){
    Column(){
      //顶部栏
      Row({space: 50}) {
        //返回键
        Text(`<`)
          .fontSize(40)
          .fontWeight(FontWeight.Bold)
          .onClick(()=>{
            router.back()
          })
        Text(`${name}`)
          .fontSize(30)
      }
      .width('95%')

      Column(){
        Text('历史数据表')
          .fontSize(30)
          .textAlign(TextAlign.Center)
        Text('尚未完成')
          .fontSize(30)
          .textAlign(TextAlign.Center)
      }
      .width('100%')
      .height('50%')
      .backgroundColor('#999999')

      Text('其他部分')
        .fontSize(30)
        .textAlign(TextAlign.Center)
    }
  }
}