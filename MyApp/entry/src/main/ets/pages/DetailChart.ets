// //显示该农田某一项数据具体信息及时间轴图标的页面
// import router from '@ohos.router'
//
// const name = router.getParams();
//
//
// @Entry
// @Component
// struct DetailChart{
//   build(){
//     Column(){
//       //顶部栏
//       Row({space: 50}) {
//         //返回键
//         Text(`<`)
//           .fontSize(40)
//           .fontWeight(FontWeight.Bold)
//           .onClick(()=>{
//             router.back()
//           })
//         Text(`${name}`)
//           .fontSize(30)
//       }
//       .width('95%')
//
//       Column(){
//         Text('历史数据表')
//           .fontSize(30)
//           .textAlign(TextAlign.Center)
//         Text('尚未完成')
//           .fontSize(30)
//           .textAlign(TextAlign.Center)
//       }
//       .width('100%')
//       .height('50%')
//       .backgroundColor('#999999')
//
//       Text('其他部分')
//         .fontSize(30)
//         .textAlign(TextAlign.Center)
//     }
//   }
// }

interface IRowItem {
  id?: number;
  title?: string;
  name1?: string;
  name2?: string;
  name3?: string;
  flag?: boolean;
  type?: string;
  onFlagChange?: () => void;
}

@Component
struct RowItem {
  private props: IRowItem;
  @Consume("flag") flag: boolean;

  build() {
    Flex() {
      Text(this.props.title)
        .fontSize(14)
        .fontWeight(FontWeight.Bold)
        .layoutWeight(1)
        .fontColor(Color.Red)
        .margin({ right: 10 })
      Flex({ alignItems: ItemAlign.Center }) {
        Text(this.props.name1).fontSize(14).margin({ right: 10 })
        Text(this.props.name2).fontSize(14).margin({ right: 10 })
        Text(this.props.name3).fontSize(14).margin({ right: 10 })

        // 当文本折叠（flag为false且type为down）时，展示展开按钮
        // 当文本展开（flag为true且type为up）时，展示折叠按钮
        if (!this.flag&&this.props.type === 'DOWN' || this.flag&&this.props.type === 'UP') {
          Image($r("app.media.water0"))
            .width(16)
            .height(16)
            .objectFit(ImageFit.Contain)
            .rotate({ angle: !this.flag&&this.props.type === 'DOWN' ? 0 : 180 })
              // 点击展开按钮后旋转180°，展示折叠按钮
            .onClick(() => this.props.onFlagChange())
            .transition({ type: TransitionType.All, opacity: 0 })
        }
      }
      .layoutWeight(3)
    }
    .width('100%')
    .height(16)
    .margin({ top: 15 })
  }
}

@Component
struct CollapseAndExpand {
  private items: IRowItem[] = [];
  @Consume("flag") flag: boolean;

  build() {
    Column() {
      ForEach(this.items, (item: IRowItem) =>{
        RowItem({ props: item })
      }, (item: IRowItem) => item.id.toString())
    }
    .width('100%')
    .clip(true)
    .height(this.flag ? 130 : 0)
  }
}

@Entry
@Component
struct CollapseAndExpandDemo {
  @Provide("flag") flag: boolean = false
  private onFlagChange = () => {
    animateTo({
      duration: 650,
      curve: Curve.Smooth },
    () => {this.flag = !this.flag;})
  }

  build() {
    Column() {
      Column() {
        RowItem({
          props: { title: '英雄', name1: 'AAAAA', name2: 'BBBBB', name3: 'CCCCC' } })
        RowItem({
          props: { name1: 'DDDDD', name2: 'EEEEE', name3: 'FFFFF',
            // 文本折叠时，type为DOWN
            type: 'DOWN', onFlagChange: this.onFlagChange
          }
        })
        // 直接调用折叠展开组件
        CollapseAndExpand({
          items: [
            { id: 0, name1: 'GGGGG', name2: 'HHHHH', name3: 'JJJJJ' },
            { id: 1, name1: 'KKKKK', name2: 'LLLLL', name3: 'MMMMM' },
            { id: 2, name1: 'NNNNN', name2: 'OOOOO', name3: 'PPPPP' },
            { id: 3,
              name1: 'QQQQQ',
              name2: 'RRRRR',
              name3: 'SSSSS',
              // 文本折叠时，type为UP
              type: 'UP',
              onFlagChange: this.onFlagChange }
          ],
        })

        RowItem({ props: { title: '商城', name1: '免费', name2: '特价', name3: 'VIP' } })
        RowItem({ props: { title: '分类', name1: '按职业', name2: '按位置', name3: '按城市' } })
      }
      .width('100%')

    }
    .height('100%')
    .padding({ top: 30, right: 30, left: 30 })
  }
}

